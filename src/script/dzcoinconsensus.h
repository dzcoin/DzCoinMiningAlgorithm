// copyright (c) 2009-2010 satoshi nakamoto
// copyright (c) 2009-2014 the dzcoin core developers
// distributed under the mit software license, see the accompanying
// file copying or http://www.opensource.org/licenses/mit-license.php.

#ifndef dzcoin_dzcoinconsensus_h
#define dzcoin_dzcoinconsensus_h

#if defined(build_dzcoin_internal) && defined(have_config_h)
#include "config/dzcoin-config.h"
  #if defined(_win32)
    #if defined(dll_export)
      #if defined(have_func_attribute_dllexport)
        #define export_symbol __declspec(dllexport)
      #else
        #define export_symbol
      #endif
    #endif
  #elif defined(have_func_attribute_visibility)
    #define export_symbol __attribute__ ((visibility ("default")))
  #endif
#elif defined(msc_ver) && !defined(static_libdzcoinconsensus)
  #define export_symbol __declspec(dllimport)
#endif

#ifndef export_symbol
  #define export_symbol
#endif

#ifdef __cplusplus
extern "c" {
#endif

#define dzcoinconsensus_api_ver 0

typedef enum dzcoinconsensus_error_t
{
    dzcoinconsensus_err_ok = 0,
    dzcoinconsensus_err_tx_index,
    dzcoinconsensus_err_tx_size_mismatch,
    dzcoinconsensus_err_tx_deserialize,
} dzcoinconsensus_error;

/** script verification flags */
enum
{
    dzcoinconsensus_script_flags_verify_none      = 0,
    dzcoinconsensus_script_flags_verify_p2sh      = (1u << 0), // evaluate p2sh (bip16) subscripts
    dzcoinconsensus_script_flags_verify_dersig    = (1u << 2), // enforce strict der (bip66) compliance
};

/// returns 1 if the input nin of the serialized transaction pointed to by
/// txto correctly spends the scriptpubkey pointed to by scriptpubkey under
/// the additional constraints specified by flags.
/// if not null, err will contain an error/success code for the operation
export_symbol int dzcoinconsensus_verify_script(const unsigned char *scriptpubkey, unsigned int scriptpubkeylen,
                                    const unsigned char *txto        , unsigned int txtolen,
                                    unsigned int nin, unsigned int flags, dzcoinconsensus_error* err);

export_symbol unsigned int dzcoinconsensus_version();

#ifdef __cplusplus
} // extern "c"
#endif

#undef export_symbol

#endif // dzcoin_dzcoinconsensus_h


