FROM amd64/debian:buster

RUN echo "root:root" | chpasswd && useradd -m -s /bin/bash progtest && \
apt-get update && apt-get install -y --no-install-recommends \
 acl \
 aptitude \
 bc \
 bzip2 \
 clang \
 doxygen \
 gcc \
 g++ \
 gdb \
 hexedit \
 joe \
 less \
 lsof \
 lzma \
 lzop \
 make \
 mc \
 openssl \
 openssh-server \
 openssh-client \
 patch \
 pmccabe \
 psmisc \
 rsync \
 screen \
 splint \
 sqlite3 \
 strace \
 unzip \
 valgrind \
 wget \
 zip \
 zstd \
 libncurses-dev \
 libsdl2-dev \
 libsdl2-gfx-dev \
 libsdl2-image-dev \
 libsdl2-mixer-dev \
 libsdl2-net-dev \
 libsdl2-ttf-dev \
 libgl-dev  \
 libglu-dev \
 freeglut3-dev \
 libssl-dev \
 zlib1g-dev \
 libmariadbclient-dev \
 libpq-dev \
 libsqlite3-dev \
 libxml2-dev \
 libpng-dev \
 libjpeg-dev \
 libexif-dev \
 libexiv2-dev \
 libmediainfo-dev && \
rm -rf /var/lib/apt/lists/*

USER progtest
RUN mkdir -p /home/progtest/vavravl3
WORKDIR /home/progtest/vavravl3
COPY . .
USER root
RUN chmod -R 777 .
USER progtest
RUN make clean
RUN make compile

CMD bash
