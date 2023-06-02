#ifndef RAYCAST_BASERESULT_HPP
#define RAYCAST_BASERESULT_HPP

#include <variant>
#include <functional>

namespace fsanvr {

    enum class ResultStatus {
        Ok,
        Error
    };

    template<typename T, typename E>
    class BaseResult {
    public:
        static constexpr BaseResult Ok(T value) noexcept {
            return BaseResult<T, E>(value);
        }
        static constexpr BaseResult Error(E error) noexcept {
            return BaseResult<T, E>(error);
        }

        T Unwrap() noexcept {
            return std::get<T>(value);
        }

        E UnwrapError() noexcept {
            return std::get<E>(value);
        }

        T UnwrapOr(T other) noexcept {
            switch(status) {
                case ResultStatus::Ok:
                    return Unwrap();
                case ResultStatus::Error:
                default:
                    return other;
            }
        }

        T UnwrapOrElse(std::function<T()> callback) noexcept {
            switch(status) {
                case ResultStatus::Ok:
                    return Unwrap();
                case ResultStatus::Error:
                    return callback();
            }
        }

        bool IsOk() noexcept {
            return status == ResultStatus::Ok;
        }

        bool IsError() noexcept {
            return !IsOk();
        }

        void Match(std::function<void(const T&)> okCallback, std::function<void(const E&)> errorCallback) {
            switch(status) {
                case ResultStatus::Ok:
                    return okCallback(Unwrap());
                case ResultStatus::Error:
                    return errorCallback(UnwrapError());
            }
        }

        ~BaseResult() = default;

    private:
        BaseResult() : value("empty"), status(ResultStatus::Error) {}
        explicit BaseResult(T value) : value(value), status(ResultStatus::Ok) {}
        explicit BaseResult(E error) : value(error), status(ResultStatus::Error) {}

        std::variant<T, E> value;
        ResultStatus status;
    };

} //namespace fsanvr

#endif //RAYCAST_BASERESULT_HPP
