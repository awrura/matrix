FROM python:3.13-slim-bookworm
ENV PLATFORMIO_VERSION="6.1.16"

RUN apt-get update && apt-get install netcat-traditional -y && apt-get autoremove -y && apt-get clean
RUN python3 -m pip install -U platformio==${PLATFORMIO_VERSION}

WORKDIR /opt

COPY ./include/ /opt/include/
COPY ./lib/ /opt/lib/
COPY ./src/ /opt/src/
COPY ./test/ /opt/test/
COPY ./CMakeLists.txt ./platformio.ini /opt/

ENTRYPOINT ["platformio"]

