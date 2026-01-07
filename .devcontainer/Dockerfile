ARG VARIANT
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

ARG ARDUINO_IDE_VERSION
ARG ARDUINO_CLI_VERSION
ARG USER_NAME
# Dialout GID standart olarak 20'dir, bunu varsayılan yapıyoruz.
ARG DIALOUT_GID=20

RUN apt update \
    && apt install -y \
    python3 \
    python3-pip \
    usbutils \
    python3-serial \
    git \
    bash-completion \
    wget \
    sudo \
    && rm -rf /var/lib/apt/lists/*

# Kullanıcıya şifresiz sudo yetkisi ver
RUN echo $USER_NAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USER_NAME \
    && chmod 0440 /etc/sudoers.d/$USER_NAME

# Kullanıcı izinleri ve grup ayarları
# Dialout grubuna eklemek seri port erişimi için kritiktir
RUN if [ $(getent group dialout) ]; then \
        usermod -a -G dialout $USER_NAME; \
    fi \
    && if grep :${DIALOUT_GID}: /etc/group; then \
        usermod -a -G $(grep :${DIALOUT_GID}: /etc/group | cut -d ':' -f 1) $USER_NAME; \
    else \
        groupadd -g ${DIALOUT_GID} vscodedialout && usermod -a -G vscodedialout $USER_NAME; \
    fi

# # Install Arduino IDE
# RUN mkdir -p /opt \
#     && cd /opt \
#     && wget https://downloads.arduino.cc/arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz \
#     && tar -xf arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz \
#     && rm -f arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz \
#     && mv arduino-${ARDUINO_IDE_VERSION} arduino \
#     && /opt/arduino/install.sh

# Install Arduino CLI
RUN mkdir -p /opt/arduino-cli \
    && cd /opt/arduino-cli \
    && wget https://github.com/arduino/arduino-cli/releases/download/v${ARDUINO_CLI_VERSION}/arduino-cli_${ARDUINO_CLI_VERSION}_Linux_64bit.tar.gz \
    && tar -xf arduino-cli_${ARDUINO_CLI_VERSION}_Linux_64bit.tar.gz \
    && rm -f arduino-cli_${ARDUINO_CLI_VERSION}_Linux_64bit.tar.gz \
    && mv arduino-cli /usr/local/bin/arduino-cli

# Set the default user
USER $USER_NAME

LABEL arduino-ide-version="${ARDUINO_IDE_VERSION}"
LABEL desccription="Image based on Debuan providing Arduino build and debug environment"

# Project specific section
# ========================

# Install any extern libraries here. Example:
# Install LiquidCrystal I2C library
# RUN arduino-cli lib install "LiquidCrystal I2C"
RUN arduino-cli config init \
    && arduino-cli config add board_manager.additional_urls https://github.com/ambiot/ambd_arduino/raw/master/Arduino_package/package_realtek_amebad_index.json \
    && arduino-cli core update-index \
    && arduino-cli core install realtek:AmebaD