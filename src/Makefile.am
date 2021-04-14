# Copyright (c) 2013-2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

# Pattern rule to print variables, e.g. make print-top_srcdir
print-%:
	@echo '$*'='$($*)'

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(GPROF_LDFLAGS) $(SANITIZER_LDFLAGS)
AM_CXXFLAGS = $(DEBUG_CXXFLAGS) $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS) $(NOWARN_CXXFLAGS) $(ERROR_CXXFLAGS) $(GPROF_CXXFLAGS) $(SANITIZER_CXXFLAGS)
AM_CPPFLAGS = $(DEBUG_CPPFLAGS) $(HARDENED_CPPFLAGS)
AM_LIBTOOLFLAGS = --preserve-dup-deps
PTHREAD_FLAGS = $(PTHREAD_CFLAGS) $(PTHREAD_LIBS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

BSVCOIN_INCLUDES=-I$(builddir) -I$(srcdir)/secp256k1/include $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS)

BSVCOIN_INCLUDES += $(UNIVALUE_CFLAGS)

LIBBSVCOIN_SERVER=libbsvcoin_server.a
LIBBSVCOIN_COMMON=libbsvcoin_common.a
LIBBSVCOIN_CONSENSUS=libbsvcoin_consensus.a
LIBBSVCOIN_CLI=libbsvcoin_cli.a
LIBBSVCOIN_UTIL=libbsvcoin_util.a
LIBBSVCOIN_CRYPTO_BASE=crypto/libbsvcoin_crypto_base.a
LIBBSVCOINQT=qt/libbsvcoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBBSVCOIN_ZMQ=libbsvcoin_zmq.a
endif
if BUILD_BSVCOIN_LIBS
LIBBSVCOINCONSENSUS=libbsvcoinconsensus.la
endif
if ENABLE_WALLET
LIBBSVCOIN_WALLET=libbsvcoin_wallet.a
LIBBSVCOIN_WALLET_TOOL=libbsvcoin_wallet_tool.a
endif

LIBBSVCOIN_CRYPTO= $(LIBBSVCOIN_CRYPTO_BASE)
if ENABLE_SSE41
LIBBSVCOIN_CRYPTO_SSE41 = crypto/libbsvcoin_crypto_sse41.a
LIBBSVCOIN_CRYPTO += $(LIBBSVCOIN_CRYPTO_SSE41)
endif
if ENABLE_AVX2
LIBBSVCOIN_CRYPTO_AVX2 = crypto/libbsvcoin_crypto_avx2.a
LIBBSVCOIN_CRYPTO += $(LIBBSVCOIN_CRYPTO_AVX2)
endif
if ENABLE_SHANI
LIBBSVCOIN_CRYPTO_SHANI = crypto/libbsvcoin_crypto_shani.a
LIBBSVCOIN_CRYPTO += $(LIBBSVCOIN_CRYPTO_SHANI)
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*.h) $(wildcard secp256k1/src/*.c) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBBSVCOIN_CRYPTO) \
  $(LIBBSVCOIN_UTIL) \
  $(LIBBSVCOIN_COMMON) \
  $(LIBBSVCOIN_CONSENSUS) \
  $(LIBBSVCOIN_SERVER) \
  $(LIBBSVCOIN_CLI) \
  $(LIBBSVCOIN_WALLET) \
  $(LIBBSVCOIN_WALLET_TOOL) \
  $(LIBBSVCOIN_ZMQ)

lib_LTLIBRARIES = $(LIBBSVCOINCONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_BSVCOIND
  bin_PROGRAMS += bsvcoind
endif

if BUILD_BSVCOIN_NODE
  bin_PROGRAMS += bsvcoin-node
endif

if BUILD_BSVCOIN_CLI
  bin_PROGRAMS += bsvcoin-cli
endif

if BUILD_BSVCOIN_TX
  bin_PROGRAMS += bsvcoin-tx
endif

if ENABLE_WALLET
if BUILD_BSVCOIN_WALLET
  bin_PROGRAMS += bsvcoin-wallet
endif
endif

if BUILD_BSVCOIN_UTIL
  bin_PROGRAMS += bsvcoin-util
endif

.PHONY: FORCE check-symbols check-security
# bsvcoin core #
BSVCOIN_CORE_H = \
  addrdb.h \
  addrman.h \
  attributes.h \
  banman.h \
  base58.h \
  bech32.h \
  blockencodings.h \
  blockfilter.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/assumptions.h \
  compat/byteswap.h \
  compat/cpuid.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_check.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  dbwrapper.h \
  external_signer.h \
  flatfile.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  i2p.h \
  index/base.h \
  index/blockfilterindex.h \
  index/disktxpos.h \
  index/txindex.h \
  indirectmap.h \
  init.h \
  interfaces/chain.h \
  interfaces/handler.h \
  interfaces/node.h \
  interfaces/wallet.h \
  key.h \
  key_io.h \
  logging.h \
  logging/timer.h \
  mapport.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_permissions.h \
  net_processing.h \
  net_types.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  node/blockstorage.h \
  node/coin.h \
  node/coinstats.h \
  node/context.h \
  node/psbt.h \
  node/transaction.h \
  node/ui_interface.h \
  node/utxo_snapshot.h \
  noui.h \
  outputtype.h \
  policy/feerate.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  policy/settings.h \
  pow.h \
  protocol.h \
  psbt.h \
  random.h \
  randomenv.h \
  reverse_iterator.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/mining.h \
  rpc/protocol.h \
  rpc/rawtransaction_util.h \
  rpc/register.h \
  rpc/request.h \
  rpc/server.h \
  rpc/util.h \
  scheduler.h \
  script/descriptor.h \
  script/keyorigin.h \
  script/sigcache.h \
  script/sign.h \
  script/signingprovider.h \
  script/standard.h \
  shutdown.h \
  signet.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadinterrupt.h \
  threadsafety.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  txorphanage.h \
  txrequest.h \
  undo.h \
  util/asmap.h \
  util/bip32.h \
  util/bytevectorhash.h \
  util/check.h \
  util/epochguard.h \
  util/error.h \
  util/fees.h \
  util/getuniquepath.h \
  util/golombrice.h \
  util/hasher.h \
  util/macros.h \
  util/message.h \
  util/moneystr.h \
  util/rbf.h \
  util/readwritefile.h \
  util/settings.h \
  util/sock.h \
  util/spanparsing.h \
  util/string.h \
  util/system.h \
  util/threadnames.h \
  util/time.h \
  util/tokenpipe.h \
  util/trace.h \
  util/translation.h \
  util/ui_change_type.h \
  util/url.h \
  util/vector.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  versionbitsinfo.h \
  wallet/bdb.h \
  wallet/coincontrol.h \
  wallet/coinselection.h \
  wallet/context.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/dump.h \
  wallet/external_signer_scriptpubkeyman.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/ismine.h \
  wallet/load.h \
  wallet/rpcwallet.h \
  wallet/salvage.h \
  wallet/scriptpubkeyman.h \
  wallet/sqlite.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/wallettool.h \
  wallet/walletutil.h \
  walletinitinterface.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h \
  zmq/zmqrpc.h \
  zmq/zmqutil.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libbsvcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between bsvcoind and bsvcoin-qt
# Contains code accessing mempool and chain state that is meant to be separated
# from wallet and gui code (see node/README.md). Shared code should go in
# libbsvcoin_common or libbsvcoin_util libraries, instead.
libbsvcoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(BSVCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(NATPMP_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libbsvcoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbsvcoin_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  banman.cpp \
  blockencodings.cpp \
  blockfilter.cpp \
  chain.cpp \
  consensus/tx_verify.cpp \
  dbwrapper.cpp \
  flatfile.cpp \
  httprpc.cpp \
  httpserver.cpp \
  i2p.cpp \
  index/base.cpp \
  index/blockfilterindex.cpp \
  index/txindex.cpp \
  init.cpp \
  mapport.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  node/blockstorage.cpp \
  node/coin.cpp \
  node/coinstats.cpp \
  node/context.cpp \
  node/interfaces.cpp \
  node/psbt.cpp \
  node/transaction.cpp \
  node/ui_interface.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/rbf.cpp \
  policy/settings.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  shutdown.cpp \
  signet.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  txorphanage.cpp \
  txrequest.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(BSVCOIN_CORE_H)

if ENABLE_WALLET
libbsvcoin_server_a_SOURCES += wallet/init.cpp
endif
if !ENABLE_WALLET
libbsvcoin_server_a_SOURCES += dummywallet.cpp
endif

if ENABLE_ZMQ
libbsvcoin_zmq_a_CPPFLAGS = $(AM_CPPFLAGS) $(BSVCOIN_INCLUDES) $(ZMQ_CFLAGS)
libbsvcoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbsvcoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp \
  zmq/zmqrpc.cpp \
  zmq/zmqutil.cpp
endif


# wallet: shared between bsvcoind and bsvcoin-qt, but only linked
# when wallet enabled
libbsvcoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(BSVCOIN_INCLUDES) $(SQLITE_CFLAGS)
libbsvcoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbsvcoin_wallet_a_SOURCES = \
  wallet/coincontrol.cpp \
  wallet/context.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/dump.cpp \
  wallet/external_signer_scriptpubkeyman.cpp \
  wallet/feebumper.cpp \
  wallet/fees.cpp \
  wallet/interfaces.cpp \
  wallet/load.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/scriptpubkeyman.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/walletutil.cpp \
  wallet/coinselection.cpp \
  $(BSVCOIN_CORE_H)

if USE_SQLITE
libbsvcoin_wallet_a_SOURCES += wallet/sqlite.cpp
endif
if USE_BDB
libbsvcoin_wallet_a_SOURCES += wallet/bdb.cpp wallet/salvage.cpp
endif

libbsvcoin_wallet_tool_a_CPPFLAGS = $(AM_CPPFLAGS) $(BSVCOIN_INCLUDES)
libbsvcoin_wallet_tool_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbsvcoin_wallet_tool_a_SOURCES = \
  wallet/wallettool.cpp \
  $(BSVCOIN_CORE_H)

# crypto primitives library
crypto_libbsvcoin_crypto_base_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libbsvcoin_crypto_base_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbsvcoin_crypto_base_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha_poly_aead.h \
  crypto/chacha_poly_aead.cpp \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hkdf_sha256_32.cpp \
  crypto/hkdf_sha256_32.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/poly1305.h \
  crypto/poly1305.cpp \
  crypto/muhash.h \
  crypto/muhash.cpp \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha3.cpp \
  crypto/sha3.h \
  crypto/sha512.cpp \
  crypto/sha512.h \
  crypto/siphash.cpp \
  crypto/siphash.h

if USE_ASM
crypto_libbsvcoin_crypto_base_a_SOURCES += crypto/sha256_sse4.cpp
endif

crypto_libbsvcoin_crypto_sse41_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbsvcoin_crypto_sse41_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libbsvcoin_crypto_sse41_a_CXXFLAGS += $(SSE41_CXXFLAGS)
crypto_libbsvcoin_crypto_sse41_a_CPPFLAGS += -DENABLE_SSE41
crypto_libbsvcoin_crypto_sse41_a_SOURCES = crypto/sha256_sse41.cpp

crypto_libbsvcoin_crypto_avx2_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbsvcoin_crypto_avx2_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libbsvcoin_crypto_avx2_a_CXXFLAGS += $(AVX2_CXXFLAGS)
crypto_libbsvcoin_crypto_avx2_a_CPPFLAGS += -DENABLE_AVX2
crypto_libbsvcoin_crypto_avx2_a_SOURCES = crypto/sha256_avx2.cpp

crypto_libbsvcoin_crypto_shani_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbsvcoin_crypto_shani_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libbsvcoin_crypto_shani_a_CXXFLAGS += $(SHANI_CXXFLAGS)
crypto_libbsvcoin_crypto_shani_a_CPPFLAGS += -DENABLE_SHANI
crypto_libbsvcoin_crypto_shani_a_SOURCES = crypto/sha256_shani.cpp

# consensus: shared between all executables that validate any consensus rules.
libbsvcoin_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(BSVCOIN_INCLUDES)
libbsvcoin_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbsvcoin_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/tx_check.cpp \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/bsvcoinconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  span.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  util/strencodings.cpp \
  util/strencodings.h \
  version.h

# common: shared between bsvcoind, and bsvcoin-qt and non-server tools
libbsvcoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(BSVCOIN_INCLUDES)
libbsvcoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbsvcoin_common_a_SOURCES = \
  base58.cpp \
  bech32.cpp \
  bloom.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  external_signer.cpp \
  key.cpp \
  key_io.cpp \
  merkleblock.cpp \
  netaddress.cpp \
  netbase.cpp \
  net_permissions.cpp \
  outputtype.cpp \
  policy/feerate.cpp \
  policy/policy.cpp \
  protocol.cpp \
  psbt.cpp \
  rpc/rawtransaction_util.cpp \
  rpc/external_signer.cpp \
  rpc/util.cpp \
  scheduler.cpp \
  script/descriptor.cpp \
  script/sign.cpp \
  script/signingprovider.cpp \
  script/standard.cpp \
  versionbitsinfo.cpp \
  warnings.cpp \
  $(BSVCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libbsvcoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(BSVCOIN_INCLUDES)
libbsvcoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbsvcoin_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  interfaces/handler.cpp \
  logging.cpp \
  random.cpp \
  randomenv.cpp \
  rpc/request.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util/asmap.cpp \
  util/bip32.cpp \
  util/bytevectorhash.cpp \
  util/error.cpp \
  util/fees.cpp \
  util/getuniquepath.cpp \
  util/hasher.cpp \
  util/sock.cpp \
  util/system.cpp \
  util/message.cpp \
  util/moneystr.cpp \
  util/rbf.cpp \
  util/readwritefile.cpp \
  util/settings.cpp \
  util/threadnames.cpp \
  util/spanparsing.cpp \
  util/strencodings.cpp \
  util/string.cpp \
  util/time.cpp \
  util/tokenpipe.cpp \
  $(BSVCOIN_CORE_H)

if USE_LIBEVENT
libbsvcoin_util_a_SOURCES += util/url.cpp
endif

if GLIBC_BACK_COMPAT
libbsvcoin_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between bsvcoin-cli and bsvcoin-qt
libbsvcoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(BSVCOIN_INCLUDES)
libbsvcoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbsvcoin_cli_a_SOURCES = \
  compat/stdin.h \
  compat/stdin.cpp \
  rpc/client.cpp \
  $(BSVCOIN_CORE_H)

nodist_libbsvcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# bsvcoind & bsvcoin-node binaries #
bsvcoin_daemon_sources = bsvcoind.cpp
bsvcoin_bin_cppflags = $(AM_CPPFLAGS) $(BSVCOIN_INCLUDES)
bsvcoin_bin_cxxflags = $(AM_CXXFLAGS) $(PIE_FLAGS)
bsvcoin_bin_ldflags = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
bsvcoin_daemon_sources += bsvcoind-res.rc
endif

bsvcoin_bin_ldadd = \
  $(LIBBSVCOIN_WALLET) \
  $(LIBBSVCOIN_COMMON) \
  $(LIBBSVCOIN_UTIL) \
  $(LIBUNIVALUE) \
  $(LIBBSVCOIN_ZMQ) \
  $(LIBBSVCOIN_CONSENSUS) \
  $(LIBBSVCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

bsvcoin_bin_ldadd += $(BOOST_LIBS) $(BDB_LIBS) $(MINIUPNPC_LIBS) $(NATPMP_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS) $(SQLITE_LIBS)

bsvcoind_SOURCES = $(bsvcoin_daemon_sources)
bsvcoind_CPPFLAGS = $(bsvcoin_bin_cppflags)
bsvcoind_CXXFLAGS = $(bsvcoin_bin_cxxflags)
bsvcoind_LDFLAGS = $(bsvcoin_bin_ldflags)
bsvcoind_LDADD = $(LIBBSVCOIN_SERVER) $(bsvcoin_bin_ldadd)

bsvcoin_node_SOURCES = $(bsvcoin_daemon_sources)
bsvcoin_node_CPPFLAGS = $(bsvcoin_bin_cppflags)
bsvcoin_node_CXXFLAGS = $(bsvcoin_bin_cxxflags)
bsvcoin_node_LDFLAGS = $(bsvcoin_bin_ldflags)
bsvcoin_node_LDADD = $(LIBBSVCOIN_SERVER) $(bsvcoin_bin_ldadd)

# bsvcoin-cli binary #
bsvcoin_cli_SOURCES = bsvcoin-cli.cpp
bsvcoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(BSVCOIN_INCLUDES) $(EVENT_CFLAGS)
bsvcoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bsvcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
bsvcoin_cli_SOURCES += bsvcoin-cli-res.rc
endif

bsvcoin_cli_LDADD = \
  $(LIBBSVCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBBSVCOIN_UTIL) \
  $(LIBBSVCOIN_CRYPTO)

bsvcoin_cli_LDADD += $(BOOST_LIBS) $(EVENT_LIBS)
#

# bsvcoin-tx binary #
bsvcoin_tx_SOURCES = bsvcoin-tx.cpp
bsvcoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(BSVCOIN_INCLUDES)
bsvcoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bsvcoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
bsvcoin_tx_SOURCES += bsvcoin-tx-res.rc
endif

bsvcoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBBSVCOIN_COMMON) \
  $(LIBBSVCOIN_UTIL) \
  $(LIBBSVCOIN_CONSENSUS) \
  $(LIBBSVCOIN_CRYPTO) \
  $(LIBSECP256K1)

bsvcoin_tx_LDADD += $(BOOST_LIBS)
#

# bsvcoin-wallet binary #
bsvcoin_wallet_SOURCES = bsvcoin-wallet.cpp
bsvcoin_wallet_CPPFLAGS = $(bsvcoin_bin_cppflags)
bsvcoin_wallet_CXXFLAGS = $(bsvcoin_bin_cxxflags)
bsvcoin_wallet_LDFLAGS = $(bsvcoin_bin_ldflags)
bsvcoin_wallet_LDADD = $(LIBBSVCOIN_WALLET_TOOL) $(bsvcoin_bin_ldadd)

if TARGET_WINDOWS
bsvcoin_wallet_SOURCES += bsvcoin-wallet-res.rc
endif
#

# bsvcoin-util binary #
bsvcoin_util_SOURCES = bsvcoin-util.cpp
bsvcoin_util_CPPFLAGS = $(AM_CPPFLAGS) $(BSVCOIN_INCLUDES)
bsvcoin_util_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bsvcoin_util_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
bsvcoin_util_SOURCES += bsvcoin-util-res.rc
endif

bsvcoin_util_LDADD = \
  $(LIBBSVCOIN_COMMON) \
  $(LIBBSVCOIN_UTIL) \
  $(LIBUNIVALUE) \
  $(LIBBSVCOIN_CONSENSUS) \
  $(LIBBSVCOIN_CRYPTO) \
  $(LIBSECP256K1)

bsvcoin_util_LDADD += $(BOOST_LIBS)
#

# bsvcoinconsensus library #
if BUILD_BSVCOIN_LIBS
include_HEADERS = script/bsvcoinconsensus.h
libbsvcoinconsensus_la_SOURCES = support/cleanse.cpp $(crypto_libbsvcoin_crypto_base_a_SOURCES) $(libbsvcoin_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libbsvcoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libbsvcoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libbsvcoinconsensus_la_LIBADD = $(LIBSECP256K1)
libbsvcoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_BSVCOIN_INTERNAL
libbsvcoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crc32c/src/*.gcda crc32c/src/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += index/*.gcda index/*.gcno
CLEANFILES += interfaces/*.gcda interfaces/*.gcno
CLEANFILES += node/*.gcda node/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += rpc/*.gcda rpc/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += util/*.gcda util/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/bsvcoin-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/bsvcoin-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/bsvcoin-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/bsvcoin-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if TARGET_DARWIN
	@echo "Checking macOS dynamic libraries..."
	$(AM_V_at) OTOOL=$(OTOOL) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)
endif

if TARGET_WINDOWS
	@echo "Checking Windows dynamic libraries..."
	$(AM_V_at) OBJDUMP=$(OBJDUMP) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)
endif

if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) CPPFILT=$(CPPFILT) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) OBJDUMP=$(OBJDUMP) OTOOL=$(OTOOL) $(PYTHON) $(top_srcdir)/contrib/devtools/security-check.py $(bin_PROGRAMS)
endif

if EMBEDDED_LEVELDB
include Makefile.crc32c.include
include Makefile.leveldb.include
endif

include Makefile.test_util.include
include Makefile.test_fuzz.include

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
