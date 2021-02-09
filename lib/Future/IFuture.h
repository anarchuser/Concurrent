#ifndef CONCURRENT_IFUTURE_H
#define CONCURRENT_IFUTURE_H

#include <thread>
#include <memory>

struct IFuture {
    virtual ~IFuture() = 0;
    IFuture (IFuture && other) noexcept;

    [[nodiscard]] virtual bool isDone() const;
    [[nodiscard]] virtual bool operator !() const;

protected:
    explicit IFuture (std::shared_ptr <std::atomic <bool>>);

private:
    std::shared_ptr <std::atomic <bool>> const done;
};

#endif //CONCURRENT_IFUTURE_H

/* Copyright (C) 2020 Aaron Alef */
