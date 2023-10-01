FROM  ubuntu:latest
RUN  apt-get update
RUN  apt-get install -y ffmpeg xauth libgtk-3-0 dbus-x11 wget zip git
RUN  dbus-uuidgen > /etc/machine-id
RUN  mkdir -p /install/ocv_tracker
RUN  wget https://github.com/vryabokon1705/ocv_tracker/releases/download/rc.0.0.1/ocv_tracker_0_0_1.zip -O /install/ocv_tracker/ocv_tracker_0_0_1.zip
RUN  cd /install/ocv_tracker && unzip ocv_tracker_0_0_1.zip
RUN  mv /install/ocv_tracker/ocv_tracker_0_0_1/lib/* /usr/local/lib
RUN  mv /install/ocv_tracker/ocv_tracker_0_0_1/ocv_tracker /usr/local/bin
RUN  ldconfig
RUN  cd /install && git clone --depth=1 https://github.com/spmallick/goturn-files.git
RUN  cd /install/goturn-files && ls
RUN  cd /install/goturn-files && cat goturn.caffemodel.zip* > goturn.caffemodel.zip
RUN  cd /install/goturn-files && unzip goturn.caffemodel.zip
RUN  mv /install/goturn-files/goturn.caffemodel /install/goturn-files/goturn.prototxt /usr/local/bin
RUN  /bin/rm -rf /install

WORKDIR /usr/local/bin
ENTRYPOINT ["/usr/local/bin/ocv_tracker"]
