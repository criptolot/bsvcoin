// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BSVCOIN_SCRIPT_BSVCOINCONSENSUS_H
#define BSVCOIN_SCRIPT_BSVCOINCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_BSVCOIN_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/bsvcoin-config.h>
  #if defined(_WIN32)
    #if defined(HAVE_DLLEXPORT_ATTRIBUTE)
      #define EXPORT_SYMBOL __declspec(dllexport)
    #else
      #define EXPORT_SYMBOL
    #endif
  #elif defined(HAVE_DEFAULT_VISIBILITY_ATTRIBUTE)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBBSVCOINCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define BSVCOINCONSENSUS_API_VER 1

typedef enum bsvcoinconsensus_error_t
{
    bsvcoinconsensus_ERR_OK = 0,
    bsvcoinconsensus_ERR_TX_INDEX,
    bsvcoinconsensus_ERR_TX_SIZE_MISMATCH,
    bsvcoinconsensus_ERR_TX_DESERIALIZE,
    bsvcoinconsensus_ERR_AMOUNT_REQUIRED,
    bsvcoinconsensus_ERR_INVALID_FLAGS,
} bsvcoinconsensus_error;

/** Script verification flags */
enum
{
    bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH | bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | bsvcoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int bsvcoinconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, bsvcoinconsensus_error* err);

EXPORT_SYMBOL int bsvcoinconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, bsvcoinconsensus_error* err);

EXPORT_SYMBOL unsigned int bsvcoinconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // BSVCOIN_SCRIPT_BSVCOINCONSENSUS_H
