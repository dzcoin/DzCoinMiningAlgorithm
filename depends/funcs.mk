﻿define int_vars
#set defaults for vars which may be overridden per-package
$(1)_cc=$($($(1)_type)_cc)
$(1)_cxx=$($($(1)_type)_cxx)
$(1)_objc=$($($(1)_type)_objc)
$(1)_objcxx=$($($(1)_type)_objcxx)
$(1)_ar=$($($(1)_type)_ar)
$(1)_ranlib=$($($(1)_type)_ranlib)
$(1)_libtool=$($($(1)_type)_libtool)
$(1)_nm=$($($(1)_type)_nm)
$(1)_cflags=$($($(1)_type)_cflags) $($($(1)_type)_$(release_type)_cflags)
$(1)_cxxflags=$($($(1)_type)_cxxflags) $($($(1)_type)_$(release_type)_cxxflags)
$(1)_ldflags=$($($(1)_type)_ldflags) $($($(1)_type)_$(release_type)_ldflags) -l$($($(1)_type)_prefix)/lib
$(1)_cppflags=$($($(1)_type)_cppflags) $($($(1)_type)_$(release_type)_cppflags) -i$($($(1)_type)_prefix)/include
$(1)_recipe_hash:=
endef

define int_get_all_dependencies
$(sort $(foreach dep,$(2),$(2) $(call int_get_all_dependencies,$(1),$($(dep)_dependencies))))
endef

define fetch_file
(test -f $$($(1)_source_dir)/$(4) || \
  ( mkdir -p $$($(1)_download_dir) && echo fetching $(1)... && \
  ( $(build_download) "$$($(1)_download_dir)/$(4).temp" "$(2)/$(3)" || \
    $(build_download) "$$($(1)_download_dir)/$(4).temp" "$(fallback_download_path)/$(3)" ) && \
    echo "$(5)  $$($(1)_download_dir)/$(4).temp" > $$($(1)_download_dir)/.$(4).hash && \
    $(build_sha256sum) -c $$($(1)_download_dir)/.$(4).hash && \
    mv $$($(1)_download_dir)/$(4).temp $$($(1)_source_dir)/$(4) && \
    rm -rf $$($(1)_download_dir) ))
endef

define int_get_build_recipe_hash
$(eval $(1)_all_file_checksums:=$(shell $(build_sha256sum) $(meta_depends) packages/$(1).mk $(addprefix $(patches_path)/$(1)/,$($(1)_patches)) | cut -d" " -f1))
$(eval $(1)_recipe_hash:=$(shell echo -n "$($(1)_all_file_checksums)" | $(build_sha256sum) | cut -d" " -f1))
endef

define int_get_build_id
$(eval $(1)_dependencies += $($(1)_$(host_arch)_$(host_os)_dependencies) $($(1)_$(host_os)_dependencies))
$(eval $(1)_all_dependencies:=$(call int_get_all_dependencies,$(1),$($($(1)_type)_native_toolchain) $($(1)_dependencies)))
$(foreach dep,$($(1)_all_dependencies),$(eval $(1)_build_id_deps+=$(dep)-$($(dep)_version)-$($(dep)_recipe_hash)))
$(eval $(1)_build_id_long:=$(1)-$($(1)_version)-$($(1)_recipe_hash)-$(release_type) $($(1)_build_id_deps))
$(eval $(1)_build_id:=$(shell echo -n "$($(1)_build_id_long)" | $(build_sha256sum) | cut -c-$(hash_length)))
final_build_id_long+=$($(package)_build_id_long)

#compute package-specific paths
$(1)_build_subdir?=.
$(1)_download_file?=$($(1)_file_name)
$(1)_source_dir:=$(sources_path)
$(1)_source:=$$($(1)_source_dir)/$($(1)_file_name)
$(1)_staging_dir=$(base_staging_dir)/$(host)/$(1)/$($(1)_version)-$($(1)_build_id)
$(1)_staging_prefix_dir:=$$($(1)_staging_dir)$($($(1)_type)_prefix)
$(1)_extract_dir:=$(base_build_dir)/$(host)/$(1)/$($(1)_version)-$($(1)_build_id)
$(1)_download_dir:=$(base_download_dir)/$(1)-$($(1)_version)
$(1)_build_dir:=$$($(1)_extract_dir)/$$($(1)_build_subdir)
$(1)_cached_checksum:=$(base_cache)/$(host)/$(1)/$(1)-$($(1)_version)-$($(1)_build_id).tar.gz.hash
$(1)_patch_dir:=$(base_build_dir)/$(host)/$(1)/$($(1)_version)-$($(1)_build_id)/.patches-$($(1)_build_id)
$(1)_prefixbin:=$($($(1)_type)_prefix)/bin/
$(1)_cached:=$(base_cache)/$(host)/$(1)/$(1)-$($(1)_version)-$($(1)_build_id).tar.gz
$(1)_all_sources=$($(1)_file_name) $($(1)_extra_sources)

#stamps
$(1)_fetched=$(sources_path)/download-stamps/.stamp_fetched-$(1)-$($(1)_file_name).hash
$(1)_extracted=$$($(1)_extract_dir)/.stamp_extracted
$(1)_preprocessed=$$($(1)_extract_dir)/.stamp_preprocessed
$(1)_cleaned=$$($(1)_extract_dir)/.stamp_cleaned
$(1)_built=$$($(1)_build_dir)/.stamp_built
$(1)_configured=$$($(1)_build_dir)/.stamp_configured
$(1)_staged=$$($(1)_staging_dir)/.stamp_staged
$(1)_postprocessed=$$($(1)_staging_prefix_dir)/.stamp_postprocessed
$(1)_download_path_fixed=$(subst :,\:,$$($(1)_download_path))


#default commands
$(1)_fetch_cmds ?= $(call fetch_file,$(1),$(subst \:,:,$$($(1)_download_path_fixed)),$$($(1)_download_file),$($(1)_file_name),$($(1)_sha256_hash))
$(1)_extract_cmds ?= mkdir -p $$($(1)_extract_dir) && echo "$$($(1)_sha256_hash)  $$($(1)_source)" > $$($(1)_extract_dir)/.$$($(1)_file_name).hash &&  $(build_sha256sum) -c $$($(1)_extract_dir)/.$$($(1)_file_name).hash && tar --strip-components=1 -xf $$($(1)_source)
$(1)_preprocess_cmds ?=
$(1)_build_cmds ?=
$(1)_config_cmds ?=
$(1)_stage_cmds ?=
$(1)_set_vars ?=


all_sources+=$$($(1)_fetched)
endef
#$(foreach dep_target,$($(1)_all_dependencies),$(eval $(1)_dependency_targets=$($(dep_target)_cached)))


define int_config_attach_build_config
$(eval $(call $(1)_set_vars,$(1)))
$(1)_cflags+=$($(1)_cflags_$(release_type))
$(1)_cflags+=$($(1)_cflags_$(host_arch)) $($(1)_cflags_$(host_arch)_$(release_type))
$(1)_cflags+=$($(1)_cflags_$(host_os)) $($(1)_cflags_$(host_os)_$(release_type))
$(1)_cflags+=$($(1)_cflags_$(host_arch)_$(host_os)) $($(1)_cflags_$(host_arch)_$(host_os)_$(release_type))

$(1)_cxxflags+=$($(1)_cxxflags_$(release_type))
$(1)_cxxflags+=$($(1)_cxxflags_$(host_arch)) $($(1)_cxxflags_$(host_arch)_$(release_type))
$(1)_cxxflags+=$($(1)_cxxflags_$(host_os)) $($(1)_cxxflags_$(host_os)_$(release_type))
$(1)_cxxflags+=$($(1)_cxxflags_$(host_arch)_$(host_os)) $($(1)_cxxflags_$(host_arch)_$(host_os)_$(release_type))

$(1)_cppflags+=$($(1)_cppflags_$(release_type))
$(1)_cppflags+=$($(1)_cppflags_$(host_arch)) $($(1)_cppflags_$(host_arch)_$(release_type))
$(1)_cppflags+=$($(1)_cppflags_$(host_os)) $($(1)_cppflags_$(host_os)_$(release_type))
$(1)_cppflags+=$($(1)_cppflags_$(host_arch)_$(host_os)) $($(1)_cppflags_$(host_arch)_$(host_os)_$(release_type))

$(1)_ldflags+=$($(1)_ldflags_$(release_type))
$(1)_ldflags+=$($(1)_ldflags_$(host_arch)) $($(1)_ldflags_$(host_arch)_$(release_type))
$(1)_ldflags+=$($(1)_ldflags_$(host_os)) $($(1)_ldflags_$(host_os)_$(release_type))
$(1)_ldflags+=$($(1)_ldflags_$(host_arch)_$(host_os)) $($(1)_ldflags_$(host_arch)_$(host_os)_$(release_type))

$(1)_build_opts+=$$($(1)_build_opts_$(release_type))
$(1)_build_opts+=$$($(1)_build_opts_$(host_arch)) $$($(1)_build_opts_$(host_arch)_$(release_type))
$(1)_build_opts+=$$($(1)_build_opts_$(host_os)) $$($(1)_build_opts_$(host_os)_$(release_type))
$(1)_build_opts+=$$($(1)_build_opts_$(host_arch)_$(host_os)) $$($(1)_build_opts_$(host_arch)_$(host_os)_$(release_type))

$(1)_config_opts+=$$($(1)_config_opts_$(release_type))
$(1)_config_opts+=$$($(1)_config_opts_$(host_arch)) $$($(1)_config_opts_$(host_arch)_$(release_type))
$(1)_config_opts+=$$($(1)_config_opts_$(host_os)) $$($(1)_config_opts_$(host_os)_$(release_type))
$(1)_config_opts+=$$($(1)_config_opts_$(host_arch)_$(host_os)) $$($(1)_config_opts_$(host_arch)_$(host_os)_$(release_type))

$(1)_config_env+=$$($(1)_config_env_$(release_type))
$(1)_config_env+=$($(1)_config_env_$(host_arch)) $($(1)_config_env_$(host_arch)_$(release_type))
$(1)_config_env+=$($(1)_config_env_$(host_os)) $($(1)_config_env_$(host_os)_$(release_type))
$(1)_config_env+=$($(1)_config_env_$(host_arch)_$(host_os)) $($(1)_config_env_$(host_arch)_$(host_os)_$(release_type))

$(1)_config_env+=pkg_config_libdir=$($($(1)_type)_prefix)/lib/pkgconfig
$(1)_config_env+=pkg_config_path=$($($(1)_type)_prefix)/share/pkgconfig
$(1)_config_env+=path=$(build_prefix)/bin:$(path)
$(1)_build_env+=path=$(build_prefix)/bin:$(path)
$(1)_stage_env+=path=$(build_prefix)/bin:$(path)
$(1)_autoconf=./configure --host=$($($(1)_type)_host) --disable-dependency-tracking --prefix=$($($(1)_type)_prefix) $$($(1)_config_opts) cc="$$($(1)_cc)" cxx="$$($(1)_cxx)"

ifneq ($($(1)_nm),)
$(1)_autoconf += nm="$$($(1)_nm)"
endif
ifneq ($($(1)_ranlib),)
$(1)_autoconf += ranlib="$$($(1)_ranlib)"
endif
ifneq ($($(1)_ar),)
$(1)_autoconf += ar="$$($(1)_ar)"
endif
ifneq ($($(1)_cflags),)
$(1)_autoconf += cflags="$$($(1)_cflags)"
endif
ifneq ($($(1)_cxxflags),)
$(1)_autoconf += cxxflags="$$($(1)_cxxflags)"
endif
ifneq ($($(1)_cppflags),)
$(1)_autoconf += cppflags="$$($(1)_cppflags)"
endif
ifneq ($($(1)_ldflags),)
$(1)_autoconf += ldflags="$$($(1)_ldflags)"
endif
endef

define int_add_cmds
$($(1)_fetched):
	$(at)mkdir -p $$(@d) $(sources_path)
	$(at)rm -f $$@
	$(at)touch $$@
	$(at)cd $$(@d); $(call $(1)_fetch_cmds,$(1))
	$(at)cd $($(1)_source_dir); $(foreach source,$($(1)_all_sources),$(build_sha256sum) $(source) >> $$(@);)
	$(at)touch $$@
$($(1)_extracted): | $($(1)_fetched)
	$(at)echo extracting $(1)...
	$(at)mkdir -p $$(@d)
	$(at)cd $$(@d); $(call $(1)_extract_cmds,$(1))
	$(at)touch $$@
$($(1)_preprocessed): | $($(1)_dependencies) $($(1)_extracted)
	$(at)echo preprocessing $(1)...
	$(at)mkdir -p $$(@d) $($(1)_patch_dir)
	$(at)$(foreach patch,$($(1)_patches),cd $(patches_path)/$(1); cp $(patch) $($(1)_patch_dir) ;)
	$(at)cd $$(@d); $(call $(1)_preprocess_cmds, $(1))
	$(at)touch $$@
$($(1)_configured): | $($(1)_preprocessed)
	$(at)echo configuring $(1)...
	$(at)rm -rf $(host_prefix); mkdir -p $(host_prefix)/lib; cd $(host_prefix); $(foreach package,$($(1)_all_dependencies), tar xf $($(package)_cached); )
	$(at)mkdir -p $$(@d)
	$(at)+cd $$(@d); $($(1)_config_env) $(call $(1)_config_cmds, $(1))
	$(at)touch $$@
$($(1)_built): | $($(1)_configured)
	$(at)echo building $(1)...
	$(at)mkdir -p $$(@d)
	$(at)+cd $$(@d); $($(1)_build_env) $(call $(1)_build_cmds, $(1))
	$(at)touch $$@
$($(1)_staged): | $($(1)_built)
	$(at)echo staging $(1)...
	$(at)mkdir -p $($(1)_staging_dir)/$(host_prefix)
	$(at)cd $($(1)_build_dir); $($(1)_stage_env) $(call $(1)_stage_cmds, $(1))
	$(at)rm -rf $($(1)_extract_dir)
	$(at)touch $$@
$($(1)_postprocessed): | $($(1)_staged)
	$(at)echo postprocessing $(1)...
	$(at)cd $($(1)_staging_prefix_dir); $(call $(1)_postprocess_cmds)
	$(at)touch $$@
$($(1)_cached): | $($(1)_dependencies) $($(1)_postprocessed)
	$(at)echo caching $(1)...
	$(at)cd $$($(1)_staging_dir)/$(host_prefix); find . | sort | tar --no-recursion -czf $$($(1)_staging_dir)/$$(@f) -t -
	$(at)mkdir -p $$(@d)
	$(at)rm -rf $$(@d) && mkdir -p $$(@d)
	$(at)mv $$($(1)_staging_dir)/$$(@f) $$(@)
	$(at)rm -rf $($(1)_staging_dir)
$($(1)_cached_checksum): $($(1)_cached)
	$(at)cd $$(@d); $(build_sha256sum) $$(<f) > $$(@)

.phony: $(1)
$(1): | $($(1)_cached_checksum)
.secondary: $($(1)_cached) $($(1)_postprocessed) $($(1)_staged) $($(1)_built) $($(1)_configured) $($(1)_preprocessed) $($(1)_extracted) $($(1)_fetched)

endef

# these functions create the build targets for each package. they must be
# broken down into small steps so that each part is done for all packages
# before moving on to the next step. otherwise, a package's info
# (build-id for example) would only be available to another package if it
# happened to be computed already.

#set the type for host/build packages.
$(foreach native_package,$(native_packages),$(eval $(native_package)_type=build))
$(foreach package,$(packages),$(eval $(package)_type=$(host_arch)_$(host_os)))

#set overridable defaults
$(foreach package,$(all_packages),$(eval $(call int_vars,$(package))))

#include package files
$(foreach package,$(all_packages),$(eval include packages/$(package).mk))

#compute a hash of all files that comprise this package's build recipe
$(foreach package,$(all_packages),$(eval $(call int_get_build_recipe_hash,$(package))))

#generate a unique id for this package, incorporating its dependencies as well
$(foreach package,$(all_packages),$(eval $(call int_get_build_id,$(package))))

#compute final vars after reading package vars
$(foreach package,$(all_packages),$(eval $(call int_config_attach_build_config,$(package))))

#create build targets
$(foreach package,$(all_packages),$(eval $(call int_add_cmds,$(package))))

#special exception: if a toolchain package exists, all non-native packages depend on it
$(foreach package,$(packages),$(eval $($(package)_unpacked): |$($($(host_arch)_$(host_os)_native_toolchain)_cached) ))

