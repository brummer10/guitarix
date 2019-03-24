	
	STRIP ?= strip
	# check if user is root
	user = $(shell whoami)
	ifeq ($(user),root)
	INSTALL_DIR = /usr/lib/lv2
	else 
	INSTALL_DIR = ~/.lv2
	endif

	# check CPU and supported optimization flags
	ifneq ($(shell cat /proc/cpuinfo | grep sse3 ) , )
		SSE_CFLAGS = -msse3 -mfpmath=sse
	else ifneq ($(shell cat /proc/cpuinfo | grep sse2 ) , )
		SSE_CFLAGS = -msse2 -mfpmath=sse
	else ifneq ($(shell cat /proc/cpuinfo | grep sse ) , )
		SSE_CFLAGS = -msse -mfpmath=sse
		else ifneq ($(shell cat /proc/cpuinfo | grep ARM ) , )
		ifneq ($(shell cat /proc/cpuinfo | grep ARMv7 ) , )
			ifneq ($(shell cat /proc/cpuinfo | grep vfpd32 ) , )
				SSE_CFLAGS = -march=armv7-a -mfpu=vfpv3 
			else ifneq ($(shell cat /proc/cpuinfo | grep vfpv3 ) , )
				SSE_CFLAGS = -march=armv7-a -mfpu=vfpv3
			endif
		else
			ARMCPU = "YES"
		endif
	else
		SSE_CFLAGS =
	endif

	# set bundle name
	NAME = gx_sceleton
	BUNDLE = $(NAME).lv2
	VER = 0.1
	# set compile flags
	CXXFLAGS += -I. -I./dsp -I./plugin -I./dsp/zita-resampler-1.1.0 -I./dsp/zita-resampler-1.1.0/zita-resampler -fPIC -DPIC -O2 -Wall -funroll-loops -ffast-math -fomit-frame-pointer -fstrength-reduce -fdata-sections -Wl,--gc-sections $(SSE_CFLAGS)
	LDFLAGS += -I. -shared -lm 
	GUI_LDFLAGS += -I./gui -shared -lm `pkg-config --cflags --libs cairo` -L/usr/X11/lib -lX11
	# invoke build files
	OBJECTS = plugin/$(NAME).cpp 
	GUI_OBJECTS = gui/$(NAME)_x11ui.c
	RES_OBJECTS = gui/pedal.o gui/pswitch.o
	## output style (bash colours)
	BLUE = "\033[1;34m"
	RED =  "\033[1;31m"
	NONE = "\033[0m"

.PHONY : mod all clean install uninstall 

all : check $(NAME)
	@mkdir -p ./$(BUNDLE)
	@cp ./plugin/*.ttl ./$(BUNDLE)
	@mv ./*.so ./$(BUNDLE)
	@if [ -f ./$(BUNDLE)/$(NAME).so ]; then echo $(BLUE)"build finish, now run make install"; \
	else echo $(RED)"sorry, build failed"; fi
	@echo $(NONE)

mod : 
	@echo "Not implemented for Gxsceleton"

check :
ifdef ARMCPU
	@echo $(RED)ARM CPU DEDECTED, please check the optimization flags
	@echo $(NONE)
endif

   #@build resource object files
$(RES_OBJECTS) : gui/pedal.png gui/pswitch.png 
	@echo $(LGREEN)"generate resource files,"$(NONE)
	-@cd ./gui && ld -r -b binary pedal.png -o pedal.o
	-@cd ./gui && ld -r -b binary pswitch.png -o pswitch.o

clean :
	@rm -f $(NAME).so
	@rm -rf ./$(BUNDLE)
	@echo ". ." $(BLUE)", clean up"$(NONE)

dist-clean :
	@rm -f $(NAME).so
	@rm -rf ./$(BUNDLE)
	@rm -rf ./$(RES_OBJECTS)
	@echo ". ." $(BLUE)", clean up"$(NONE)

install :
ifneq ("$(wildcard ./$(BUNDLE))","")
	@mkdir -p $(DESTDIR)$(INSTALL_DIR)/$(BUNDLE)
	cp -r ./$(BUNDLE)/* $(DESTDIR)$(INSTALL_DIR)/$(BUNDLE)
	@echo ". ." $(BLUE)", done"$(NONE)
else
	@echo ". ." $(BLUE)", you must build first"$(NONE)
endif

uninstall :
	@rm -rf $(INSTALL_DIR)/$(BUNDLE)
	@echo ". ." $(BLUE)", done"$(NONE)

$(NAME) : clean $(RES_OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME).so
	$(CC) $(CXXFLAGS) -Wl,-z,nodelete $(GUI_OBJECTS) $(RES_OBJECTS) $(GUI_LDFLAGS) -o $(NAME)_ui.so
	$(STRIP) -s -x -X -R .comment -R .eh_frame -R .eh_frame_hdr -R .note.gnu.build-id -R .note.ABI-tag $(NAME).so
	$(STRIP) -s -x -X -R .comment -R .eh_frame -R .eh_frame_hdr -R .note.gnu.build-id -R .note.ABI-tag $(NAME)_ui.so

nogui : clean
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME).so
	$(STRIP) -s -x -X -R .comment -R .eh_frame -R .eh_frame_hdr -R .note.gnu.build-id -R .note.ABI-tag $(NAME).so
