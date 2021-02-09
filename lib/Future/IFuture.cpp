#include "IFuture.h"

IFuture::IFuture (std::shared_ptr <std::atomic <bool>> done): done {std::move (done)} {}
IFuture::~IFuture() = default;

bool IFuture::isDone() const {
    return * done;
}
bool IFuture::operator !() const {
    return !isDone();
}

/* Copyright (C) 2021 Aaron Alef */
