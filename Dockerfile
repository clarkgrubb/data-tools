FROM alpine:3.5
RUN apk update && apk add \
    bash \
    diffutils \
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

RUN ln -s /usr/bin/ruby2.2 /usr/bin/ruby

RUN mkdir /app
WORKDIR /app

RUN gem2.2 install json nokogiri rubocop

COPY requirements.txt /app/requirements.txt
RUN pip3 install -r requirements.txt

COPY . /app
RUN make check

ENTRYPOINT ./src/dt.sh
# CMD make