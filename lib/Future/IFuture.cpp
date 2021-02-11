#include "IFuture.h"

IFuture::IFuture (std::shared_ptr <std::atomic <bool>> done): done {std::move (done)} {}
IFuture::IFuture (IFuture && other) noexcept: done {other.done} {}
IFuture::~IFuture() = default;

bool IFuture::isDone() const {
    return * done;
}
bool IFuture::operator !() const {
    return !isDone();
}

/* Copyright (C) 2021 Aaron Alef */
