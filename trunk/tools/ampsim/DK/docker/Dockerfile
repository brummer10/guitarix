FROM debian:10

COPY python_venv add_dkbuilder_script add_geda_custom_symbols /root/

RUN apt-get -y update &&\
    #
    # list of packages
    #
    # geda packages are for viewing editing electric circuit schematics
    # (to start the geda program in a container you would need to set the
    #  DISPLAY environment variable; please check the web on how to do this
    #  in a container)
    #
    # git is just for convenience
    #
    # the other packages are more or less essential:
    #
    apt-get -y install \
      faust \
      geda \
      geda-gattrib \
      geda-gnetlist \
      geda-gschem \
      geda-gsymcheck \
      geda-symbols \
      git \
      libcminpack-dev \
      libeigen3-dev \
      libserial-dev \
      libslicot0 \
      libsundials-dev \
      lv2-dev \
      maxima \
      python-dev \
      python-tk \
      python-virtualenv \
      virtualenv \
      virtualenvwrapper \
      &&\
    #
    # create the Python virtual environment
    bash -c ". /usr/share/virtualenvwrapper/virtualenvwrapper.sh \
             && mkvirtualenv -r ~/python_venv guitarix" &&\
    #
    # add dkbuilder shell function to enter the virtual environment
    ~/add_dkbuilder_script /mnt/data &&\
    # add script to add custom geda symbols
    ~/add_geda_custom_symbols /mnt/data
