VULKAN_SDK_PATH = ./lib/vulkan/x86_64
CFLAGS = -std=c++17 -I $(VULKAN_SDK_PATH)/include
LDFLAGS = -L $(VULKAN_SDK_PATH)/lib -lvulkan

default: build

build:
	g++ $(CFLAGS) src/main.cpp src/Instance.cpp  $(LDFLAGS) -o bin/sapere

test:
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/vulkan/explicit_layer.d ./bin/sapere
	
clean:
	rm bin/sapere

# g++ $(CFLAGS) src/main.cpp src/test.cpp $(LDFLAGS) -o bin/sapere