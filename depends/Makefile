.notparallel :

sources_path ?= $(basedir)/sources
base_cache ?= $(basedir)/built
sdk_path ?= $(basedir)/sdks
no_qt ?=
no_wallet ?=
no_upnp ?=
fallback_download_path ?= https://dzcoincore.org/depends-sources

build = $(shell ./config.guess)
host ?= $(build)
patches_path = $(basedir)/patches
basedir = $(curdir)
hash_length:=11
download_connect_timeout:=10
download_retries:=3

host:=$(build)
ifneq ($(host),)
host:=$(host)
host_toolchain:=$(host)-
endif

ifneq ($(debug),)
release_type=debug
else
release_type=release
endif

base_build_dir=$(basedir)/work/build
base_staging_dir=$(basedir)/work/staging
base_download_dir=$(basedir)/work/download
canonical_host:=$(shell ./config.sub $(host))
build:=$(shell ./config.sub $(build))

build_arch =$(firstword $(subst -, ,$(build)))
build_vendor=$(word 2,$(subst -, ,$(build)))
full_build_os:=$(subst $(build_arch)-$(build_vendor)-,,$(build))
build_os:=$(findstring linux,$(full_build_os))
build_os+=$(findstring darwin,$(full_build_os))
build_os:=$(strip $(build_os))
ifeq ($(build_os),)
build_os=$(full_build_os)
endif

host_arch=$(firstword $(subst -, ,$(canonical_host)))
host_vendor=$(word 2,$(subst -, ,$(canonical_host)))
full_host_os:=$(subst $(host_arch)-$(host_vendor)-,,$(canonical_host))
host_os:=$(findstring linux,$(full_host_os))
host_os+=$(findstring darwin,$(full_host_os))
host_os+=$(findstring mingw32,$(full_host_os))
host_os:=$(strip $(host_os))
ifeq ($(host_os),)
host_os=$(full_host_os)
endif

$(host_arch)_$(host_os)_prefix=$(basedir)/$(host)
$(host_arch)_$(host_os)_host=$(host)
host_prefix=$($(host_arch)_$(host_os)_prefix)
build_prefix=$(host_prefix)/native
build_host=$(build)

at_$(v):=
at_:=@
at:=$(at_$(v))

all: install

include hosts/$(host_os).mk
include hosts/default.mk
include builders/$(build_os).mk
include builders/default.mk
include packages/packages.mk

qt_packages_$(no_qt) = $(qt_packages) $(qt_$(host_os)_packages)
qt_native_packages_$(no_qt) = $(qt_native_packages)
wallet_packages_$(no_wallet) = $(wallet_packages)
upnp_packages_$(no_upnp) = $(upnp_packages)

packages += $($(host_arch)_$(host_os)_packages) $($(host_os)_packages) $(qt_packages_) $(wallet_packages_) $(upnp_packages_)
native_packages += $($(host_arch)_$(host_os)_native_packages) $($(host_os)_native_packages) $(qt_native_packages_)
all_packages = $(packages) $(native_packages)

meta_depends = makefile funcs.mk builders/default.mk hosts/default.mk hosts/$(host_os).mk builders/$(build_os).mk

$(host_arch)_$(host_os)_native_toolchain?=$($(host_os)_native_toolchain)

include funcs.mk

toolchain_path=$($($(host_arch)_$(host_os)_native_toolchain)_prefixbin)
final_build_id_long+=$(shell $(build_sha256sum) config.site.in)
final_build_id+=$(shell echo -n $(final_build_id_long) | $(build_sha256sum) | cut -c-$(hash_length))
$(host_prefix)/.stamp_$(final_build_id): $(native_packages) $(packages)
	$(at)rm -rf $(@d)
	$(at)mkdir -p $(@d)
	$(at)echo copying packages: $^
	$(at)echo to: $(@d)
	$(at)cd $(@d); $(foreach package,$^, tar xf $($(package)_cached); )
	$(at)touch $@

$(host_prefix)/share/config.site : config.site.in $(host_prefix)/.stamp_$(final_build_id)
	$(at)@mkdir -p $(@d)
	$(at)sed -e 's|@host@|$(host)|' \
            -e 's|@cc@|$(toolchain_path)$(host_cc)|' \
            -e 's|@cxx@|$(toolchain_path)$(host_cxx)|' \
            -e 's|@ar@|$(toolchain_path)$(host_ar)|' \
            -e 's|@ranlib@|$(toolchain_path)$(host_ranlib)|' \
            -e 's|@nm@|$(toolchain_path)$(host_nm)|' \
            -e 's|@strip@|$(toolchain_path)$(host_strip)|' \
            -e 's|@build_os@|$(build_os)|' \
            -e 's|@host_os@|$(host_os)|' \
            -e 's|@cflags@|$(strip $(host_cflags) $(host_$(release_type)_cflags))|' \
            -e 's|@cxxflags@|$(strip $(host_cxxflags) $(host_$(release_type)_cxxflags))|' \
            -e 's|@cppflags@|$(strip $(host_cppflags) $(host_$(release_type)_cppflags))|' \
            -e 's|@ldflags@|$(strip $(host_ldflags) $(host_$(release_type)_ldflags))|' \
            -e 's|@no_qt@|$(no_qt)|' \
            -e 's|@no_wallet@|$(no_wallet)|' \
            -e 's|@no_upnp@|$(no_upnp)|' \
            -e 's|@debug@|$(debug)|' \
            $< > $@
	$(at)touch $@


define check_or_remove_cached
  mkdir -p $(base_cache)/$(host)/$(package) && cd $(base_cache)/$(host)/$(package); \
  $(build_sha256sum) -c $($(package)_cached_checksum) >/dev/null 2>/dev/null || \
  ( rm -f $($(package)_cached_checksum); \
    if test -f "$($(package)_cached)"; then echo "checksum mismatch for $(package). forcing rebuild.."; rm -f $($(package)_cached_checksum) $($(package)_cached); fi )
endef

define check_or_remove_sources
  mkdir -p $($(package)_source_dir); cd $($(package)_source_dir); \
  $(build_sha256sum) -c $($(package)_fetched) >/dev/null 2>/dev/null || \
    ( if test -f $($(package)_all_sources); then echo "checksum missing or mismatched for $(package) source. forcing re-download."; fi; \
      rm -f $($(package)_all_sources) $($(1)_fetched))
endef

check-packages:
	@$(foreach package,$(all_packages),$(call check_or_remove_cached,$(package));)
check-sources:
	@$(foreach package,$(all_packages),$(call check_or_remove_sources,$(package));)

$(host_prefix)/share/config.site: check-packages

check-packages: check-sources

install: check-packages $(host_prefix)/share/config.site


download-one: check-sources $(all_sources)

download-osx:
	@$(make) -s host=x86_64-apple-darwin11 download-one
download-linux:
	@$(make) -s host=x86_64-unknown-linux-gnu download-one
download-win:
	@$(make) -s host=x86_64-w64-mingw32 download-one
download: download-osx download-linux download-win

.phony: install cached download-one download-osx download-linux download-win download check-packages check-sources


