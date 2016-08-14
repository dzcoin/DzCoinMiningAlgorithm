// copyright (c) 2011-2014 the dzcoin core developers
// distributed under the mit software license, see the accompanying
// file copying or http://www.opensource.org/licenses/mit-license.php.

#include "dzcoinamountfield.h"

#include "dzcoinunits.h"
#include "guiconstants.h"
#include "qvaluecombobox.h"

#include <qapplication>
#include <qabstractspinbox>
#include <qhboxlayout>
#include <qkeyevent>
#include <qlineedit>

/** qspinbox that uses fixed-point numbers internally and uses our own
 * formatting/parsing functions.
 */
class amountspinbox: public qabstractspinbox
{
    q_object

public:
    explicit amountspinbox(qwidget *parent):
        qabstractspinbox(parent),
        currentunit(dzcoinunits::btc),
        singlestep(100000) // satoshis
    {
        setalignment(qt::alignright);

        connect(lineedit(), signal(textedited(qstring)), this, signal(valuechanged()));
    }

    qvalidator::state validate(qstring &text, int &pos) const
    {
        if(text.isempty())
            return qvalidator::intermediate;
        bool valid = false;
        parse(text, &valid);
        /* make sure we return intermediate so that fixup() is called on defocus */
        return valid ? qvalidator::intermediate : qvalidator::invalid;
    }

    void fixup(qstring &input) const
    {
        bool valid = false;
        camount val = parse(input, &valid);
        if(valid)
        {
            input = dzcoinunits::format(currentunit, val, false, dzcoinunits::separatoralways);
            lineedit()->settext(input);
        }
    }

    camount value(bool *valid_out=0) const
    {
        return parse(text(), valid_out);
    }

    void setvalue(const camount& value)
    {
        lineedit()->settext(dzcoinunits::format(currentunit, value, false, dzcoinunits::separatoralways));
        emit valuechanged();
    }

    void stepby(int steps)
    {
        bool valid = false;
        camount val = value(&valid);
        val = val + steps * singlestep;
        val = qmin(qmax(val, camount(0)), dzcoinunits::maxmoney());
        setvalue(val);
    }

    void setdisplayunit(int unit)
    {
        bool valid = false;
        camount val = value(&valid);

        currentunit = unit;

        if(valid)
            setvalue(val);
        else
            clear();
    }

    void setsinglestep(const camount& step)
    {
        singlestep = step;
    }

    qsize minimumsizehint() const
    {
        if(cachedminimumsizehint.isempty())
        {
            ensurepolished();

            const qfontmetrics fm(fontmetrics());
            int h = lineedit()->minimumsizehint().height();
            int w = fm.width(dzcoinunits::format(dzcoinunits::btc, dzcoinunits::maxmoney(), false, dzcoinunits::separatoralways));
            w += 2; // cursor blinking space

            qstyleoptionspinbox opt;
            initstyleoption(&opt);
            qsize hint(w, h);
            qsize extra(35, 6);
            opt.rect.setsize(hint + extra);
            extra += hint - style()->subcontrolrect(qstyle::cc_spinbox, &opt,
                                                    qstyle::sc_spinboxeditfield, this).size();
            // get closer to final result by repeating the calculation
            opt.rect.setsize(hint + extra);
            extra += hint - style()->subcontrolrect(qstyle::cc_spinbox, &opt,
                                                    qstyle::sc_spinboxeditfield, this).size();
            hint += extra;
            hint.setheight(h);

            opt.rect = rect();

            cachedminimumsizehint = style()->sizefromcontents(qstyle::ct_spinbox, &opt, hint, this)
                                    .expandedto(qapplication::globalstrut());
        }
        return cachedminimumsizehint;
    }

private:
    int currentunit;
    camount singlestep;
    mutable qsize cachedminimumsizehint;

    /**
     * parse a string into a number of base monetary units and
     * return validity.
     * @note must return 0 if !valid.
     */
    camount parse(const qstring &text, bool *valid_out=0) const
    {
        camount val = 0;
        bool valid = dzcoinunits::parse(currentunit, text, &val);
        if(valid)
        {
            if(val < 0 || val > dzcoinunits::maxmoney())
                valid = false;
        }
        if(valid_out)
            *valid_out = valid;
        return valid ? val : 0;
    }

protected:
    bool event(qevent *event)
    {
        if (event->type() == qevent::keypress || event->type() == qevent::keyrelease)
        {
            qkeyevent *keyevent = static_cast<qkeyevent *>(event);
            if (keyevent->key() == qt::key_comma)
            {
                // translate a comma into a period
                qkeyevent periodkeyevent(event->type(), qt::key_period, keyevent->modifiers(), ".", keyevent->isautorepeat(), keyevent->count());
                return qabstractspinbox::event(&periodkeyevent);
            }
        }
        return qabstractspinbox::event(event);
    }

    stepenabled stepenabled() const
    {
        if (isreadonly()) // disable steps when amountspinbox is read-only
            return stepnone;
        if (text().isempty()) // allow step-up with empty field
            return stepupenabled;

        stepenabled rv = 0;
        bool valid = false;
        camount val = value(&valid);
        if(valid)
        {
            if(val > 0)
                rv |= stepdownenabled;
            if(val < dzcoinunits::maxmoney())
                rv |= stepupenabled;
        }
        return rv;
    }

signals:
    void valuechanged();
};

#include "dzcoinamountfield.moc"

dzcoinamountfield::dzcoinamountfield(qwidget *parent) :
    qwidget(parent),
    amount(0)
{
    amount = new amountspinbox(this);
    amount->setlocale(qlocale::c());
    amount->installeventfilter(this);
    amount->setmaximumwidth(170);

    qhboxlayout *layout = new qhboxlayout(this);
    layout->addwidget(amount);
    unit = new qvaluecombobox(this);
    unit->setmodel(new dzcoinunits(this));
    layout->addwidget(unit);
    layout->addstretch(1);
    layout->setcontentsmargins(0,0,0,0);

    setlayout(layout);

    setfocuspolicy(qt::tabfocus);
    setfocusproxy(amount);

    // if one if the widgets changes, the combined content changes as well
    connect(amount, signal(valuechanged()), this, signal(valuechanged()));
    connect(unit, signal(currentindexchanged(int)), this, slot(unitchanged(int)));

    // set default based on configuration
    unitchanged(unit->currentindex());
}

void dzcoinamountfield::clear()
{
    amount->clear();
    unit->setcurrentindex(0);
}

void dzcoinamountfield::setenabled(bool fenabled)
{
    amount->setenabled(fenabled);
    unit->setenabled(fenabled);
}

bool dzcoinamountfield::validate()
{
    bool valid = false;
    value(&valid);
    setvalid(valid);
    return valid;
}

void dzcoinamountfield::setvalid(bool valid)
{
    if (valid)
        amount->setstylesheet("");
    else
        amount->setstylesheet(style_invalid);
}

bool dzcoinamountfield::eventfilter(qobject *object, qevent *event)
{
    if (event->type() == qevent::focusin)
    {
        // clear invalid flag on focus
        setvalid(true);
    }
    return qwidget::eventfilter(object, event);
}

qwidget *dzcoinamountfield::setuptabchain(qwidget *prev)
{
    qwidget::settaborder(prev, amount);
    qwidget::settaborder(amount, unit);
    return unit;
}

camount dzcoinamountfield::value(bool *valid_out) const
{
    return amount->value(valid_out);
}

void dzcoinamountfield::setvalue(const camount& value)
{
    amount->setvalue(value);
}

void dzcoinamountfield::setreadonly(bool freadonly)
{
    amount->setreadonly(freadonly);
}

void dzcoinamountfield::unitchanged(int idx)
{
    // use description tooltip for current unit for the combobox
    unit->settooltip(unit->itemdata(idx, qt::tooltiprole).tostring());

    // determine new unit id
    int newunit = unit->itemdata(idx, dzcoinunits::unitrole).toint();

    amount->setdisplayunit(newunit);
}

void dzcoinamountfield::setdisplayunit(int newunit)
{
    unit->setvalue(newunit);
}

void dzcoinamountfield::setsinglestep(const camount& step)
{
    amount->setsinglestep(step);
}


