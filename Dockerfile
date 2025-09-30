# Multi-stage Dockerfile (опционально)
FROM gcc:12.2.0 as builder

# Устанавливаем зависимости для сборки
RUN apt-get update && apt-get install -y \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .
RUN make all

FROM gcc:12.2.0 as runtime
WORKDIR /app
COPY --from=builder /app/matrix_app .
COPY --from=builder /app/test_app .

# Для документации можно оставить отдельный stage
FROM builder as docs
RUN apt-get update && apt-get install -y \
    doxygen \
    graphviz \
    && rm -rf /var/lib/apt/lists/*
RUN make docs

# Основной runtime образ
FROM runtime
CMD ["./matrix_app"]