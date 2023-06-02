#include <catch2/catch_all.hpp>

#include <string>
#include <tuple>

#include "../../Engine/Result/Result.hpp"

using namespace fsanvr;

TEST_CASE( "Result can be created", "[Result][unwrap]") {
    using ValueType = int;
    using ErrorType = std::string;


    SECTION( "with error" ) {
        ErrorType error = "default error";

        auto result = BaseResult<ValueType, ErrorType>::Error(error);

        REQUIRE( result.IsError() == true );
    }

    SECTION( "with value" ) {
        ValueType value = 5;

        auto result = BaseResult<ValueType, ErrorType>::Ok(value);

        REQUIRE( result.IsOk() == true );
    }
}

TEST_CASE( "Result can be unwrapped", "[Result][create]") {
    using ValueType = int;
    using ErrorType = std::string;
    ErrorType error = "default error";

    SECTION( "with error") {
        auto result = BaseResult<ValueType, ErrorType>::Error(error);

        REQUIRE( result.IsError() == true );
        REQUIRE( result.UnwrapError() == error );
    }

    SECTION( "with value") {
        ValueType value = 50;
        auto result = BaseResult<ValueType, ErrorType>::Ok(value);

        REQUIRE( result.IsOk() == true );
        REQUIRE( result.Unwrap() == value );
    }

    SECTION( "with default value") {
        ValueType defaultValue = -1;

        auto result = BaseResult<ValueType, ErrorType>::Error(error);

        REQUIRE( result.IsError() == true );
        REQUIRE( result.UnwrapOr(defaultValue) == defaultValue );
    }

    SECTION( "with computed value") {
        auto computeValue = [](){ return 1 + 2*5; };

        auto result = BaseResult<ValueType, ErrorType>::Error(error);

        REQUIRE( result.IsError() == true );
        REQUIRE( result.UnwrapOrElse(computeValue) == computeValue() );
    }
}

TEST_CASE( "Result can be matched", "[Result][match]") {
    using ValueType = int;
    using ErrorType = std::string;
    ErrorType error = "default error";

    SECTION( "with error callback" ) {
        auto result = BaseResult<ValueType, ErrorType>::Error(error);
        ErrorType matchCheckValue = error;
        auto expectedValue = error + error;

        result.Match([&](auto val) {
            return;
            }, [&](auto err) {
            matchCheckValue = err + err;
        });

        REQUIRE( matchCheckValue == expectedValue );
    }

    SECTION( "with value callback" ) {
        ValueType value = 5;
        auto result = BaseResult<ValueType, ErrorType>::Ok(value);
        ValueType matchCheckValue = value;
        auto expectedValue = value + value;

        result.Match([&](auto val) {
            matchCheckValue = val + val;
        }, [&](auto err) {
            return;
        });

        REQUIRE( matchCheckValue == expectedValue );
    }
}

