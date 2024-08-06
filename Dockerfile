FROM drogonframework/drogon:latest

RUN sudo apt-get install libjsoncpp-dev && sudo ln -s /usr/include/jsoncpp/json/ /usr/include/json

COPY . /app

WORKDIR /app

EXPOSE 5555

RUN mkdir build && \
    cd build && \
    cmake ..  && \
    make

CMD [ "/app/build/qc-transport-service" ]
