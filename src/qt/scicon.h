// copyright (c) 2014 the dzcoin developers
// distributed under the mit software license, see the accompanying
// file copying or http://www.opensource.org/licenses/mit-license.php.

#ifndef dzcoin_qt_scicon_h
#define dzcoin_qt_scicon_h

#include <qtcore>

qt_begin_namespace
class qcolor;
class qicon;
class qstring;
qt_end_namespace

qimage singlecolorimage(const qstring& filename, const qcolor&);
qicon singlecoloricon(const qicon&, const qcolor&);
qicon singlecoloricon(const qstring& filename, const qcolor&);
qcolor singlecolor();
qicon singlecoloricon(const qstring& filename);
qicon textcoloricon(const qicon&);
qicon textcoloricon(const qstring& filename);

#endif // dzcoin_qt_scicon_h


