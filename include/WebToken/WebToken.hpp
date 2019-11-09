#pragma once

/**
 * @file WebToken.hpp
 *
 * This module declares the WebToken::WebToken class.
 *
 * © 2019 by Richard Walters
 */

#include <Json/Value.hpp>
#include <memory>
#include <ostream>
#include <stdint.h>
#include <string>
#include <vector>

namespace WebToken {

    /**
     * This class represents a JSON Web Token (JWT), as specified
     * in RFC 7519 (https://tools.ietf.org/html/rfc7519).
     */
    class WebToken {
        // Lifecycle management
    public:
        ~WebToken() noexcept;
        WebToken(const WebToken&);
        WebToken(WebToken&&) noexcept;
        WebToken& operator=(const WebToken&);
        WebToken& operator=(WebToken&&) noexcept;

        // Public methods
    public:
        /**
         * This constructs a JWT from its encoding.
         *
         * @param[in] encoding
         *     This is the encoding of the JWT to represent.
         */
        explicit WebToken(const std::string& encoding);

        /**
         * Return the content of the JWT that is used to generate
         * or verify the JWT's signature.
         *
         * @return
         *     The content of the JWT that is used to generate
         *     or verify the JWT's signature is returned.
         */
        std::vector< uint8_t > GetData() const;

        /**
         * Return the header of the JWT.
         *
         * @return
         *     The header of the JWT is returned.
         */
        Json::Value GetHeader() const;

        /**
         * Return the payload of the JWT.
         *
         * @return
         *     The payload of the JWT is returned.
         */
        Json::Value GetPayload() const;

        /**
         * Return the signature of the JWT.
         *
         * @return
         *     The signature of the JWT is returned.
         */
        std::vector< uint8_t > GetSignature() const;

        // Private properties
    private:
        /**
         * This is the type of structure that contains the private
         * properties of the instance.  It is defined in the implementation
         * and declared here to ensure that it is scoped inside the class.
         */
        struct Impl;

        /**
         * This contains the private properties of the instance.
         */
        std::unique_ptr< Impl > impl_;
    };

}
