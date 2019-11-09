/**
 * @file WebToken.cpp
 *
 * This module contains the implementation of the WebToken::WebToken class.
 *
 * © 2019 by Richard Walters
 */

#include <Base64/Base64.hpp>
#include <Json/Value.hpp>
#include <WebToken/WebToken.hpp>
#include <stdint.h>
#include <string>
#include <vector>

namespace WebToken {

    /**
     * This contains the private properties of a WebToken instance.
     */
    struct WebToken::Impl {
        /**
         * This is the content of the JWT that is used to generate
         * or verify the JWT's signature.
         */
        std::vector< uint8_t > data;

        /**
         * This is the first part of the JWT, which describes what it is
         * and how it's signed (if it's signed).
         */
        Json::Value header;

        /**
         * This is the main body of the JWT.  In the case of OpenID Connect,
         * this would be the set of claims embodied in the token.
         */
        Json::Value payload;

        /**
         * This is the last part of the JWT, typically containing the
         * cryptographic signature used to verify the token was actually
         * issued by the issuer, and not tampered with.
         */
        std::vector< uint8_t > signature;
    };

    WebToken::~WebToken() noexcept = default;
    WebToken::WebToken(const WebToken& other)
        : impl_(new Impl)
    {
        *impl_ = *other.impl_;
    }
    WebToken::WebToken(WebToken&& other) noexcept
        : impl_(nullptr)
    {
        impl_ = std::move(other.impl_);
    }
    WebToken& WebToken::operator=(WebToken&& other) noexcept {
        if (this != &other) {
            impl_ = std::move(other.impl_);
        }
        return *this;
    }
    WebToken& WebToken::operator=(const WebToken& other) {
        if (this != &other) {
            impl_.reset(new Impl());
            *impl_ = *other.impl_;
        }
        return *this;
    }

    WebToken::WebToken(const std::string& encoding)
        : impl_(new Impl)
    {
        auto delimiter = encoding.find('.');
        if (delimiter == std::string::npos) {
            impl_->header = encoding;
            return;
        }
        const auto encodedHeader = encoding.substr(0, delimiter);
        impl_->header = Json::Value::FromEncoding(
            Base64::UrlDecode(
                encodedHeader
            )
        );
        auto remainder = encoding.substr(delimiter + 1);
        delimiter = remainder.find('.');
        if (delimiter == std::string::npos) {
            impl_->payload = remainder;
            return;
        }
        const auto encodedPayload = remainder.substr(0, delimiter);
        impl_->payload = Json::Value::FromEncoding(
            Base64::UrlDecode(
                encodedPayload
            )
        );
        const auto dataAsString = encodedHeader + "." + encodedPayload;
        impl_->data.assign(dataAsString.begin(), dataAsString.end());
        remainder = remainder.substr(delimiter + 1);
        const auto signatureAsString = Base64::UrlDecode(remainder);
        impl_->signature.assign(
            signatureAsString.begin(),
            signatureAsString.end()
        );
    }

    std::vector< uint8_t > WebToken::GetData() const {
        return impl_->data;
    }

    Json::Value WebToken::GetHeader() const {
        return impl_->header;
    }

    Json::Value WebToken::GetPayload() const {
        return impl_->payload;
    }

    std::vector< uint8_t > WebToken::GetSignature() const {
        return impl_->signature;
    }

}
