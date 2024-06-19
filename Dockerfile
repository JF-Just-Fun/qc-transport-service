FROM drogonframework/drogon:latest

WORKDIR /app

COPY . .

# 创建 build 目录并运行 cmake 和 make
RUN cmake .
RUN make

EXPOSE 10947

CMD ["./qc-transport-service"]
