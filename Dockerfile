FROM alpine:3.5
RUN apk update && apk add \
    bash \
    gcc \
    make \
    musl-dev \
    python3 \
    ruby2.2 \
    ruby2.2-dev \
    ruby2.2-irb \
    ruby2.2-rake \
    ruby2.2-rdoc \
    zlib-dev

RUN mkdir /app
WORKDIR /app

COPY Makefile /app/Makefile
RUN make setup.ruby
RUN make setup.python

COPY . /app
RUN make check

ENTRYPOINT ./src/dt.sh