﻿

#include <qtglobal>

// automatically generated by extract_strings.py
#ifdef __gnuc__
#define unused __attribute__((unused))
#else
#define unused
#endif
static const char unused *dzcoin_strings[] = {
qt_translate_noop("dzcoin-core", ""
"(1 = keep tx meta data e.g. account owner and payment request information, 2 "
"= drop tx meta data)"),
qt_translate_noop("dzcoin-core", ""
"allow json-rpc connections from specified source. valid for <ip> are a "
"single ip (e.g. 1.2.3.4), a network/netmask (e.g. 1.2.3.4/255.255.255.0) or "
"a network/cidr (e.g. 1.2.3.4/24). this option can be specified multiple times"),
qt_translate_noop("dzcoin-core", ""
"an error occurred while setting up the rpc address %s port %u for listening: "
"%s"),
qt_translate_noop("dzcoin-core", ""
"bind to given address and always listen on it. use [host]:port notation for "
"ipv6"),
qt_translate_noop("dzcoin-core", ""
"bind to given address and whitelist peers connecting to it. use [host]:port "
"notation for ipv6"),
qt_translate_noop("dzcoin-core", ""
"bind to given address to listen for json-rpc connections. use [host]:port "
"notation for ipv6. this option can be specified multiple times (default: "
"bind to all interfaces)"),
qt_translate_noop("dzcoin-core", ""
"cannot obtain a lock on data directory %s. dzcoin core is probably already "
"running."),
qt_translate_noop("dzcoin-core", ""
"continuously rate-limit free transactions to <n>*1000 bytes per minute "
"(default: %u)"),
qt_translate_noop("dzcoin-core", ""
"create new files with system default permissions, instead of umask 077 (only "
"effective with disabled wallet functionality)"),
qt_translate_noop("dzcoin-core", ""
"delete all wallet transactions and only recover those parts of the "
"blockchain through -rescan on startup"),
qt_translate_noop("dzcoin-core", ""
"discover own ip addresses (default: 1 when listening and no -externalip or -"
"proxy)"),
qt_translate_noop("dzcoin-core", ""
"distributed under the mit software license, see the accompanying file "
"copying or <http://www.opensource.org/licenses/mit-license.php>."),
qt_translate_noop("dzcoin-core", ""
"enter regression test mode, which uses a special chain in which blocks can "
"be solved instantly."),
qt_translate_noop("dzcoin-core", ""
"error: listening for incoming connections failed (listen returned error %s)"),
qt_translate_noop("dzcoin-core", ""
"error: unsupported argument -socks found. setting socks version isn't "
"possible anymore, only socks5 proxies are supported."),
qt_translate_noop("dzcoin-core", ""
"execute command when a relevant alert is received or we see a really long "
"fork (%s in cmd is replaced by message)"),
qt_translate_noop("dzcoin-core", ""
"execute command when a wallet transaction changes (%s in cmd is replaced by "
"txid)"),
qt_translate_noop("dzcoin-core", ""
"execute command when the best block changes (%s in cmd is replaced by block "
"hash)"),
qt_translate_noop("dzcoin-core", ""
"fees (in btc/kb) smaller than this are considered zero fee for relaying "
"(default: %s)"),
qt_translate_noop("dzcoin-core", ""
"fees (in btc/kb) smaller than this are considered zero fee for transaction "
"creation (default: %s)"),
qt_translate_noop("dzcoin-core", ""
"flush database activity from memory pool to disk log every <n> megabytes "
"(default: %u)"),
qt_translate_noop("dzcoin-core", ""
"how thorough the block verification of -checkblocks is (0-4, default: %u)"),
qt_translate_noop("dzcoin-core", ""
"if paytxfee is not set, include enough fee so transactions begin "
"confirmation on average within n blocks (default: %u)"),
qt_translate_noop("dzcoin-core", ""
"in this mode -genproclimit controls how many blocks are generated "
"immediately."),
qt_translate_noop("dzcoin-core", ""
"invalid amount for -maxtxfee=<amount>: '%s' (must be at least the minrelay "
"fee of %s to prevent stuck transactions)"),
qt_translate_noop("dzcoin-core", ""
"log transaction priority and fee per kb when mining blocks (default: %u)"),
qt_translate_noop("dzcoin-core", ""
"maintain a full transaction index, used by the getrawtransaction rpc call "
"(default: %u)"),
qt_translate_noop("dzcoin-core", ""
"maximum size of data in data carrier transactions we relay and mine "
"(default: %u)"),
qt_translate_noop("dzcoin-core", ""
"maximum total fees to use in a single wallet transaction; setting this too "
"low may abort large transactions (default: %s)"),
qt_translate_noop("dzcoin-core", ""
"number of seconds to keep misbehaving peers from reconnecting (default: %u)"),
qt_translate_noop("dzcoin-core", ""
"output debugging information (default: %u, supplying <category> is optional)"),
qt_translate_noop("dzcoin-core", ""
"prune configured below the minimum of %d mb.  please use a higher number."),
qt_translate_noop("dzcoin-core", ""
"query for peer addresses via dns lookup, if low on addresses (default: 1 "
"unless -connect)"),
qt_translate_noop("dzcoin-core", ""
"randomize credentials for every proxy connection. this enables tor stream "
"isolation (default: %u)"),
qt_translate_noop("dzcoin-core", ""
"reduce storage requirements by pruning (deleting) old blocks. this mode "
"disables wallet support and is incompatible with -txindex. warning: "
"reverting this setting requires re-downloading the entire blockchain. "
"(default: 0 = disable pruning blocks, >%u = target size in mib to use for "
"block files)"),
qt_translate_noop("dzcoin-core", ""
"require high priority for relaying free or low-fee transactions (default: %u)"),
qt_translate_noop("dzcoin-core", ""
"set maximum size of high-priority/low-fee transactions in bytes (default: %d)"),
qt_translate_noop("dzcoin-core", ""
"set the number of script verification threads (%u to %d, 0 = auto, <0 = "
"leave that many cores free, default: %d)"),
qt_translate_noop("dzcoin-core", ""
"set the number of threads for coin generation if enabled (-1 = all cores, "
"default: %d)"),
qt_translate_noop("dzcoin-core", ""
"the transaction amount is too small to send after the fee has been deducted"),
qt_translate_noop("dzcoin-core", ""
"this is a pre-release test build - use at your own risk - do not use for "
"mining or merchant applications"),
qt_translate_noop("dzcoin-core", ""
"this product includes software developed by the openssl project for use in "
"the openssl toolkit <https://www.openssl.org/> and cryptographic software "
"written by eric young and upnp software written by thomas bernard."),
qt_translate_noop("dzcoin-core", ""
"to use dzcoind, or the -server option to dzcoin-qt, you must set an "
"rpcpassword in the configuration file:\n"
"%s\n"
"it is recommended you use the following random password:\n"
"rpcuser=dzcoinrpc\n"
"rpcpassword=%s\n"
"(you do not need to remember this password)\n"
"the username and password must not be the same.\n"
"if the file does not exist, create it with owner-readable-only file "
"permissions.\n"
"it is also recommended to set alertnotify so you are notified of problems;\n"
"for example: alertnotify=echo %%s | mail -s \"dzcoin alert\" admin@foo.com\n"),
qt_translate_noop("dzcoin-core", ""
"unable to bind to %s on this computer. dzcoin core is probably already "
"running."),
qt_translate_noop("dzcoin-core", ""
"use separate socks5 proxy to reach peers via tor hidden services (default: "
"%s)"),
qt_translate_noop("dzcoin-core", ""
"warning: -maxtxfee is set very high! fees this large could be paid on a "
"single transaction."),
qt_translate_noop("dzcoin-core", ""
"warning: -paytxfee is set very high! this is the transaction fee you will "
"pay if you send a transaction."),
qt_translate_noop("dzcoin-core", ""
"warning: please check that your computer's date and time are correct! if "
"your clock is wrong dzcoin core will not work properly."),
qt_translate_noop("dzcoin-core", ""
"warning: the network does not appear to fully agree! some miners appear to "
"be experiencing issues."),
qt_translate_noop("dzcoin-core", ""
"warning: we do not appear to fully agree with our peers! you may need to "
"upgrade, or other nodes may need to upgrade."),
qt_translate_noop("dzcoin-core", ""
"warning: error reading wallet.dat! all keys read correctly, but transaction "
"data or address book entries might be missing or incorrect."),
qt_translate_noop("dzcoin-core", ""
"warning: wallet.dat corrupt, data salvaged! original wallet.dat saved as "
"wallet.{timestamp}.bak in %s; if your balance or transactions are incorrect "
"you should restore from a backup."),
qt_translate_noop("dzcoin-core", ""
"whitelist peers connecting from the given netmask or ip address. can be "
"specified multiple times."),
qt_translate_noop("dzcoin-core", ""
"whitelisted peers cannot be dos banned and their transactions are always "
"relayed, even if they are already in the mempool, useful e.g. for a gateway"),
qt_translate_noop("dzcoin-core", ""
"you need to rebuild the database using -reindex to go back to unpruned "
"mode.  this will redownload the entire blockchain"),
qt_translate_noop("dzcoin-core", "(default: %s)"),
qt_translate_noop("dzcoin-core", "(default: %u)"),
qt_translate_noop("dzcoin-core", "(default: 1)"),
qt_translate_noop("dzcoin-core", "<category> can be:"),
qt_translate_noop("dzcoin-core", "accept command line and json-rpc commands"),
qt_translate_noop("dzcoin-core", "accept connections from outside (default: 1 if no -proxy or -connect)"),
qt_translate_noop("dzcoin-core", "accept public rest requests (default: %u)"),
qt_translate_noop("dzcoin-core", "acceptable ciphers (default: %s)"),
qt_translate_noop("dzcoin-core", "activating best chain..."),
qt_translate_noop("dzcoin-core", "add a node to connect to and attempt to keep the connection open"),
qt_translate_noop("dzcoin-core", "allow dns lookups for -addnode, -seednode and -connect"),
qt_translate_noop("dzcoin-core", "allow self signed root certificates (default: 0)"),
qt_translate_noop("dzcoin-core", "always query for peer addresses via dns lookup (default: %u)"),
qt_translate_noop("dzcoin-core", "attempt to recover private keys from a corrupt wallet.dat"),
qt_translate_noop("dzcoin-core", "block creation options:"),
qt_translate_noop("dzcoin-core", "can't run with a wallet in prune mode."),
qt_translate_noop("dzcoin-core", "cannot downgrade wallet"),
qt_translate_noop("dzcoin-core", "cannot resolve -bind address: '%s'"),
qt_translate_noop("dzcoin-core", "cannot resolve -externalip address: '%s'"),
qt_translate_noop("dzcoin-core", "cannot resolve -whitebind address: '%s'"),
qt_translate_noop("dzcoin-core", "cannot write default address"),
qt_translate_noop("dzcoin-core", "choose data directory on startup (default: 0)"),
qt_translate_noop("dzcoin-core", "connect only to the specified node(s)"),
qt_translate_noop("dzcoin-core", "connect through socks5 proxy"),
qt_translate_noop("dzcoin-core", "connect to a node to retrieve peer addresses, and disconnect"),
qt_translate_noop("dzcoin-core", "connection options:"),
qt_translate_noop("dzcoin-core", "copyright (c) 2009-%i the dzcoin core developers"),
qt_translate_noop("dzcoin-core", "corrupted block database detected"),
qt_translate_noop("dzcoin-core", "could not parse -rpcbind value %s as network address"),
qt_translate_noop("dzcoin-core", "debugging/testing options:"),
qt_translate_noop("dzcoin-core", "disable safemode, override a real safe mode event (default: %u)"),
qt_translate_noop("dzcoin-core", "do not load the wallet and disable wallet rpc calls"),
qt_translate_noop("dzcoin-core", "do you want to rebuild the block database now?"),
qt_translate_noop("dzcoin-core", "done loading"),
qt_translate_noop("dzcoin-core", "error initializing block database"),
qt_translate_noop("dzcoin-core", "error initializing wallet database environment %s!"),
qt_translate_noop("dzcoin-core", "error loading block database"),
qt_translate_noop("dzcoin-core", "error loading wallet.dat"),
qt_translate_noop("dzcoin-core", "error loading wallet.dat: wallet corrupted"),
qt_translate_noop("dzcoin-core", "error loading wallet.dat: wallet requires newer version of dzcoin core"),
qt_translate_noop("dzcoin-core", "error opening block database"),
qt_translate_noop("dzcoin-core", "error reading from database, shutting down."),
qt_translate_noop("dzcoin-core", "error"),
qt_translate_noop("dzcoin-core", "error: a fatal internal error occured, see debug.log for details"),
qt_translate_noop("dzcoin-core", "error: disk space is low!"),
qt_translate_noop("dzcoin-core", "error: unsupported argument -tor found, use -onion."),
qt_translate_noop("dzcoin-core", "failed to listen on any port. use -listen=0 if you want this."),
qt_translate_noop("dzcoin-core", "fee (in btc/kb) to add to transactions you send (default: %s)"),
qt_translate_noop("dzcoin-core", "force safe mode (default: %u)"),
qt_translate_noop("dzcoin-core", "generate coins (default: %u)"),
qt_translate_noop("dzcoin-core", "how many blocks to check at startup (default: %u, 0 = all)"),
qt_translate_noop("dzcoin-core", "if <category> is not supplied, output all debugging information."),
qt_translate_noop("dzcoin-core", "importing..."),
qt_translate_noop("dzcoin-core", "imports blocks from external blk000??.dat file"),
qt_translate_noop("dzcoin-core", "include ip addresses in debug output (default: %u)"),
qt_translate_noop("dzcoin-core", "incorrect or no genesis block found. wrong datadir for network?"),
qt_translate_noop("dzcoin-core", "information"),
qt_translate_noop("dzcoin-core", "initialization sanity check failed. dzcoin core is shutting down."),
qt_translate_noop("dzcoin-core", "insufficient funds"),
qt_translate_noop("dzcoin-core", "invalid -onion address: '%s'"),
qt_translate_noop("dzcoin-core", "invalid -proxy address: '%s'"),
qt_translate_noop("dzcoin-core", "invalid amount for -maxtxfee=<amount>: '%s'"),
qt_translate_noop("dzcoin-core", "invalid amount for -minrelaytxfee=<amount>: '%s'"),
qt_translate_noop("dzcoin-core", "invalid amount for -mintxfee=<amount>: '%s'"),
qt_translate_noop("dzcoin-core", "invalid amount for -paytxfee=<amount>: '%s' (must be at least %s)"),
qt_translate_noop("dzcoin-core", "invalid amount for -paytxfee=<amount>: '%s'"),
qt_translate_noop("dzcoin-core", "invalid netmask specified in -whitelist: '%s'"),
qt_translate_noop("dzcoin-core", "keep at most <n> unconnectable transactions in memory (default: %u)"),
qt_translate_noop("dzcoin-core", "limit size of signature cache to <n> entries (default: %u)"),
qt_translate_noop("dzcoin-core", "listen for json-rpc connections on <port> (default: %u or testnet: %u)"),
qt_translate_noop("dzcoin-core", "listen for connections on <port> (default: %u or testnet: %u)"),
qt_translate_noop("dzcoin-core", "loading addresses..."),
qt_translate_noop("dzcoin-core", "loading block index..."),
qt_translate_noop("dzcoin-core", "loading wallet..."),
qt_translate_noop("dzcoin-core", "maintain at most <n> connections to peers (default: %u)"),
qt_translate_noop("dzcoin-core", "make the wallet broadcast transactions"),
qt_translate_noop("dzcoin-core", "maximum per-connection receive buffer, <n>*1000 bytes (default: %u)"),
qt_translate_noop("dzcoin-core", "maximum per-connection send buffer, <n>*1000 bytes (default: %u)"),
qt_translate_noop("dzcoin-core", "need to specify a port with -whitebind: '%s'"),
qt_translate_noop("dzcoin-core", "node relay options:"),
qt_translate_noop("dzcoin-core", "not enough file descriptors available."),
qt_translate_noop("dzcoin-core", "only accept block chain matching built-in checkpoints (default: %u)"),
qt_translate_noop("dzcoin-core", "only connect to nodes in network <net> (ipv4, ipv6 or onion)"),
qt_translate_noop("dzcoin-core", "options:"),
qt_translate_noop("dzcoin-core", "password for json-rpc connections"),
qt_translate_noop("dzcoin-core", "prepend debug output with timestamp (default: %u)"),
qt_translate_noop("dzcoin-core", "prune cannot be configured with a negative value."),
qt_translate_noop("dzcoin-core", "prune mode is incompatible with -txindex."),
qt_translate_noop("dzcoin-core", "rpc ssl options: (see the dzcoin wiki for ssl setup instructions)"),
qt_translate_noop("dzcoin-core", "rpc server options:"),
qt_translate_noop("dzcoin-core", "rpc support for http persistent connections (default: %d)"),
qt_translate_noop("dzcoin-core", "randomly drop 1 of every <n> network messages"),
qt_translate_noop("dzcoin-core", "randomly fuzz 1 of every <n> network messages"),
qt_translate_noop("dzcoin-core", "rebuild block chain index from current blk000??.dat files on startup"),
qt_translate_noop("dzcoin-core", "relay and mine data carrier transactions (default: %u)"),
qt_translate_noop("dzcoin-core", "relay non-p2sh multisig (default: %u)"),
qt_translate_noop("dzcoin-core", "rescan the block chain for missing wallet transactions"),
qt_translate_noop("dzcoin-core", "rescanning..."),
qt_translate_noop("dzcoin-core", "run a thread to flush wallet periodically (default: %u)"),
qt_translate_noop("dzcoin-core", "run in the background as a daemon and accept commands"),
qt_translate_noop("dzcoin-core", "send trace/debug info to console instead of debug.log file"),
qt_translate_noop("dzcoin-core", "send transactions as zero-fee transactions if possible (default: %u)"),
qt_translate_noop("dzcoin-core", "server certificate file (default: %s)"),
qt_translate_noop("dzcoin-core", "server private key (default: %s)"),
qt_translate_noop("dzcoin-core", "set ssl root certificates for payment request (default: -system-)"),
qt_translate_noop("dzcoin-core", "set database cache size in megabytes (%d to %d, default: %d)"),
qt_translate_noop("dzcoin-core", "set key pool size to <n> (default: %u)"),
qt_translate_noop("dzcoin-core", "set language, for example \"de_de\" (default: system locale)"),
qt_translate_noop("dzcoin-core", "set maximum block size in bytes (default: %d)"),
qt_translate_noop("dzcoin-core", "set minimum block size in bytes (default: %u)"),
qt_translate_noop("dzcoin-core", "set the number of threads to service rpc calls (default: %d)"),
qt_translate_noop("dzcoin-core", "sets the db_private flag in the wallet db environment (default: %u)"),
qt_translate_noop("dzcoin-core", "show all debugging options (usage: --help -help-debug)"),
qt_translate_noop("dzcoin-core", "show splash screen on startup (default: 1)"),
qt_translate_noop("dzcoin-core", "shrink debug.log file on client startup (default: 1 when no -debug)"),
qt_translate_noop("dzcoin-core", "signing transaction failed"),
qt_translate_noop("dzcoin-core", "specify configuration file (default: %s)"),
qt_translate_noop("dzcoin-core", "specify connection timeout in milliseconds (minimum: 1, default: %d)"),
qt_translate_noop("dzcoin-core", "specify data directory"),
qt_translate_noop("dzcoin-core", "specify pid file (default: %s)"),
qt_translate_noop("dzcoin-core", "specify wallet file (within data directory)"),
qt_translate_noop("dzcoin-core", "specify your own public address"),
qt_translate_noop("dzcoin-core", "spend unconfirmed change when sending transactions (default: %u)"),
qt_translate_noop("dzcoin-core", "start minimized"),
qt_translate_noop("dzcoin-core", "stop running after importing blocks from disk (default: %u)"),
qt_translate_noop("dzcoin-core", "the transaction amount is too small to pay the fee"),
qt_translate_noop("dzcoin-core", "this help message"),
qt_translate_noop("dzcoin-core", "this is experimental software."),
qt_translate_noop("dzcoin-core", "this is intended for regression testing tools and app development."),
qt_translate_noop("dzcoin-core", "threshold for disconnecting misbehaving peers (default: %u)"),
qt_translate_noop("dzcoin-core", "transaction amount too small"),
qt_translate_noop("dzcoin-core", "transaction amounts must be positive"),
qt_translate_noop("dzcoin-core", "transaction too large for fee policy"),
qt_translate_noop("dzcoin-core", "transaction too large"),
qt_translate_noop("dzcoin-core", "ui options:"),
qt_translate_noop("dzcoin-core", "unable to bind to %s on this computer (bind returned error %s)"),
qt_translate_noop("dzcoin-core", "unknown network specified in -onlynet: '%s'"),
qt_translate_noop("dzcoin-core", "upgrade wallet to latest format"),
qt_translate_noop("dzcoin-core", "use openssl (https) for json-rpc connections"),
qt_translate_noop("dzcoin-core", "use upnp to map the listening port (default: %u)"),
qt_translate_noop("dzcoin-core", "use upnp to map the listening port (default: 1 when listening)"),
qt_translate_noop("dzcoin-core", "use the test network"),
qt_translate_noop("dzcoin-core", "username for json-rpc connections"),
qt_translate_noop("dzcoin-core", "verifying blocks..."),
qt_translate_noop("dzcoin-core", "verifying wallet..."),
qt_translate_noop("dzcoin-core", "wallet %s resides outside data directory %s"),
qt_translate_noop("dzcoin-core", "wallet needed to be rewritten: restart dzcoin core to complete"),
qt_translate_noop("dzcoin-core", "wallet options:"),
qt_translate_noop("dzcoin-core", "warning"),
qt_translate_noop("dzcoin-core", "warning: this version is obsolete; upgrade required!"),
qt_translate_noop("dzcoin-core", "warning: unsupported argument -benchmark ignored, use -debug=bench."),
qt_translate_noop("dzcoin-core", "warning: unsupported argument -debugnet ignored, use -debug=net."),
qt_translate_noop("dzcoin-core", "you need to rebuild the database using -reindex to change -txindex"),
qt_translate_noop("dzcoin-core", "zapping all transactions from wallet..."),
qt_translate_noop("dzcoin-core", "on startup"),
qt_translate_noop("dzcoin-core", "wallet.dat corrupt, salvage failed"),
};


