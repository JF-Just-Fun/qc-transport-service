FROM drogonframework/drogon:latest

WORKDIR /app

COPY . .

# 创建 build 目录并运行 cmake 和 make
RUN mkdir -p build \
    && cd build \
    && cmake .. \
    && make

EXPOSE 5555

CMD ["./build/qc-transport-service"]
