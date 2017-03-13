FROM alpine:3.5
RUN apk update \
    && apk add \
    bash \
    diffutils \
    gcc \
    make \
    man \
    musl-dev \
    python3 \
    ruby2.2 \
    ruby2.2-dev \
    ruby2.2-irb \
    ruby2.2-rake \
    ruby2.2-rdoc \
    zlib-dev \
    && ln -s /usr/bin/ruby2.2 /usr/bin/ruby \
    && mkdir /app

WORKDIR /app

RUN GEM_HOME=.gems gem2.2 install rubocop

COPY requirements.txt /app/requirements.txt
RUN python3 -m venv ve \
    && . ve/bin/activate \
    && pip install -r requirements.txt

COPY . /app
RUN make check \
    && mkdir /app/bin \
    && LOCAL_INSTALL_DIR=/app/bin make install \
    && make dt.sh

ENTRYPOINT ["./dt"]
# CMD make