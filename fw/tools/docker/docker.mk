# Makefiles including this should set the DOCKERFILES var
# to a list of image names.
#
# For each image $(i) the following targets will be defined:
#
# docker-build-$(i): builds the image from Dockerfile-$(i)
# docker-push-$(i): pushes the image as $(REGISTRY)/$(i)

REPO_PATH ?= $(realpath ../../../..)
REGISTRY ?= docker.io/mgos
DOCKER_TAG ?= latest
DOCKER_FLAGS ?=

all: docker-build

docker-build: $(foreach i,$(DOCKERFILES),docker-build-$(i))
docker-push: $(foreach i,$(DOCKERFILES),docker-push-$(i))

docker-pre-build-%: Dockerfile-%
	@true

docker-build-%: docker-pre-build-%
	@echo Building $(REGISTRY)/$*:$(DOCKER_TAG)
	docker build $(DOCKER_FLAGS) -t $(REGISTRY)/$*:$(DOCKER_TAG) -f Dockerfile-$* .
	@echo Built $(REGISTRY)/$*:$(DOCKER_TAG)

docker-push-%:
	docker push $(REGISTRY)/$*:$(DOCKER_TAG)

fw_meta.py: $(REPO_PATH)/common/tools/fw_meta.py
	cp -v $< .

serve_core.py: $(REPO_PATH)/common/tools/serve_core.py
	cp -v $< .

mkspiffs mkspiffs8:
	rm -rf vfs-fs-spiffs
	git clone --depth=1 https://github.com/mongoose-os-libs/vfs-fs-spiffs
	docker run --rm -it \
	  -v $(CURDIR)/vfs-fs-spiffs:/vfs-fs-spiffs \
	  docker.io/mgos/gcc \
	  bash -c 'make -C /vfs-fs-spiffs/tools mkspiffs mkspiffs8 \
	    SPIFFS_CONFIG_PATH=$(SPIFFS_CONFIG_PATH)'
	cp -v vfs-fs-spiffs/tools/$@ $@
