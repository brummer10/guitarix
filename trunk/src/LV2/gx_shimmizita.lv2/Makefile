	
	# check if user is root
	user = $(shell whoami)
	ifeq ($(user),root)
	INSTALL_DIR = /usr/lib/lv2
	else 
	INSTALL_DIR = ~/.lv2
	endif
	
	ifneq (cat /proc/cpuinfo | grep sse2 >/dev/null,)
	SSE_CFLAGS = -msse2 -mfpmath=sse
	else ifneq (cat /proc/cpuinfo | grep sse >/dev/null,)
	SSE_CFLAGS = -msse -mfpmath=sse
	else
	SSE_CFLAGS = ""
	endif
	
	# set bundle name
	NAME = gx_shimmizita
	BUNDLE = $(NAME).lv2
	VER = 0.1
	# set compile flags
	CXXFLAGS = -I. -I../DSP  -O2 -Wall -funroll-loops -ffast-math -fomit-frame-pointer -fstrength-reduce $(SSE_CFLAGS)
	LDFLAGS = -I. -I../DSP -shared -Llibrary -lc -lm  -fPIC -DPIC  
	# invoke build files
	OBJECTS = $(NAME).cpp 
	## output style (bash colours)
	BLUE = "\033[1;34m"
	RED =  "\033[1;31m"
	NONE = "\033[0m"

.PHONY : all clean install uninstall 

all : $(NAME)
	@mkdir -p ./$(BUNDLE)
	@cp ./*.ttl ./$(BUNDLE)
	@mv ./*.so ./$(BUNDLE)
	@if [ -f ./$(BUNDLE)/$(NAME).so ]; then echo $(BLUE)"build finish, now run make install"; \
	else echo $(RED)"sorry, build failed"; fi
	@echo $(NONE)

clean :
	@rm -f $(NAME).so
	@rm -rf ./$(BUNDLE)
	@echo ". ." $(BLUE)", done"$(NONE)

install : all
	@mkdir -p $(DESTDIR)$(INSTALL_DIR)/$(BUNDLE)
	install ./$(BUNDLE)/* $(DESTDIR)$(INSTALL_DIR)/$(BUNDLE)
	@echo ". ." $(BLUE)", done"$(NONE)

uninstall :
	@rm -rf $(INSTALL_DIR)/$(BUNDLE)
	@echo ". ." $(BLUE)", done"$(NONE)

$(NAME) :
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME).so
