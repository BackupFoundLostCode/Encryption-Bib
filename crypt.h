//
// Created by varcolac on 15.08.26.
//
#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <string>

#ifndef LABOR_FOR_ENCRYPTION_CRYPT_H
#define LABOR_FOR_ENCRYPTION_CRYPT_H

#endif //LABOR_FOR_ENCRYPTION_CRYPT_H

inline std::vector<std::bitset<8>> string_to_bitset(const std::string &str) {
    std::vector<std::bitset<8>> keyInCell;
    keyInCell.resize(str.size()/8);

    for (size_t i = 0; i < keyInCell.size(); i++){
        std::string byte = str.substr(i * 8, 8);
        keyInCell[i] = std::bitset<8>(byte);
    }

    return keyInCell;
}

inline std::vector <std::bitset<8>> ascii_to_bit(const std::string &textToBit) {
    std::vector<std::bitset<8>> bitsFromAscii = {};

    for (auto i = 0; i < textToBit.length(); i++) {
        std::bitset<8> bits(textToBit[i]);
        bitsFromAscii.push_back(bits);
    }

    return bitsFromAscii;
}

inline void bit_to_ascii(const std::vector<std::bitset<8>> &textInBit) {
    for (auto i : textInBit) {
        std::cout << static_cast<char>(i.to_ullong());
    }
}

inline int real_random_numbers() {

    int result = {};
    std::random_device rd;

    if (rd.entropy()==0) {
        std::cout << "KEIN ECHTER ZUFALL AUF DEM SYSTEM MÖGLICH!" << std::endl;
        return 404;
    }
    std::uniform_int_distribution<int> myBit (0,1);
    const int zufallswert = myBit(rd);
    result = zufallswert;

    return result;
}

inline int rest(const int number, const int modulo) {
    return number % modulo;
}

inline int rest_big_number(const int number, const int expo, const int modulo) {
    return static_cast<int>(std::pow(number, expo)) % modulo;
}

inline bool ggT(const int number, const int modulo) {
    return std::gcd(number, modulo) == 1;
}

namespace affineEncryption {
    inline std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWKYZ";


    inline int affine_Encryption(const int keyA, const int keyB, const int index) {
        int result = {};

        if (ggT(keyA, 26)) {
            int chiff = ((keyA* index) + keyB) % 26;
            result = chiff;
        }
        else {
            std::cout << "FATAL ERROR!" << std::endl;
        }

        return result;
    }

    inline int affine_Decryption(const int keyA, const int keyB, const int index) {
        int result = {};

        if (ggT(keyA, 26)) {

            int reverse = {1};
            bool run = true;

            while (run) {

                if ((keyA * reverse) % 26 == 1) {
                    
                    int dCrypt = reverse * (index - keyB) % 26;

                    if (dCrypt < 0) {
                        dCrypt =(dCrypt +26) %26;
                    }
                    run = false;
                    result = dCrypt;
                }
                else {
                    reverse++;
                }
            }
        }
        return result;
    }
}

namespace streamCipher  {

    inline std::vector<std::bitset<8>> stream_key_OTP(const std::vector<std::bitset<8>> &messageBitLenght) {

        std::vector<std::bitset<8>> key;
        key.resize(messageBitLenght.size());

        for (auto i = 0; i < messageBitLenght.size(); i++) {
            for (auto j = 0; j < 8; j++) {
                key[i][j] = real_random_numbers();
            }
        }
        std::cout << "THIS IS YOUR KEY, SAFE THE KEY IN BIT: " << std::endl;
        for (auto i : key) {
            std::cout << i;
        }

        return key;
    }
    //
    inline std::vector<std::bitset<8>> stream_verschlusseln_OTP(const std::vector<std::bitset<8>> &textInBit, const std::vector<std::bitset<8>> &strom) {
        std::vector<std::bitset<8>> message;
        message.resize(textInBit.size());

        for (auto i = 0; i < message.size(); i++) {
            for (auto j = 0; j < 8; j++) {
                message[i][j] = (textInBit[i][j] + strom[i][j])%2;
            }
        }

        return message;
    }
    //
    inline void stream_entschlusseln_OTP(const std::string &keyToString, const std::string &verMessage) {
        std::vector<std::bitset<8>> keyInCell;
        std::vector< std::bitset<8>> newMessage;
        std::vector<std::bitset<8>> message = string_to_bitset(verMessage);

        message.resize(keyToString.size()/8);
        keyInCell.resize(keyToString.size()/8);
        newMessage.resize(keyToString.size()/8);

        if (keyToString.size()%8 !=0 || keyToString.size() !=  verMessage.size()) {
            std::cout << "Nicht genug Bit vorhanden, Key und Nachricht müssen die gleiche anzahl Bit haben." << std::endl;
            std::cout << "Länge Key: " << keyToString.length() << std::endl;
            std::cout << "Länge der verschlüsselten Nachricht: : " << verMessage.size() << std::endl;

            exit(1);
        }

        keyInCell = string_to_bitset(keyToString);

        for (auto i = 0; i < newMessage.size(); i++) {
            for (auto j = 0; j < 8; j++) {
                newMessage[i][j] = (keyInCell[i][j] + message[i][j])%2;
            }
        }

        std::cout << "Your Message:" << std::endl;
        bit_to_ascii(newMessage);
    }

}
//
//
namespace advance {

    inline void right_shift_register(const int chiffts) {
        std::bitset<8> shiftRegister;

        for (auto i = 0; i < 8; i++) {
            shiftRegister[i] = real_random_numbers();
        }

        std::cout << "Das gestezte bitset:" << std::endl;
        for (auto i = 0; i < shiftRegister.size(); i++) {
            std::cout <<shiftRegister[shiftRegister.size() - 1 -i];
        }

        std::cout << "\n" << std::endl;
        std::cout << "EIN VERSUCH:" << std::endl;
        for (auto i = 0; i < chiffts; i++) {

            bool lastBit2 = shiftRegister[0];
            shiftRegister >>= 1;
            shiftRegister[7]= lastBit2;

            for (auto j = 0; j < shiftRegister.size(); j++) {
                std::cout <<shiftRegister[shiftRegister.size() - 1 -j];
            }
            std::cout << "" << std::endl;
        }
    }

    inline void right_shift_register_feedback(const int chiffts) {
        std::bitset<8> shiftRegister;

        for (auto i = 0; i < 8; i++) {
            shiftRegister[i] = real_random_numbers();
        }

        std::cout << "\n" << std::endl;
        std::cout << "EIN VERSUCH (Pseudoranddomzahlen über Schieberegister):" << std::endl;
        for (auto i = 0; i < chiffts; i++) {

            bool feedback = shiftRegister[2] ^ shiftRegister[4];
            shiftRegister >>= 1;
            shiftRegister[7]= feedback;

            for (auto j = 0; j < shiftRegister.size(); j++) {
                std::cout <<shiftRegister[shiftRegister.size() - 1 -j];
            }
            std::cout << "" << std::endl;
        }
    }

    namespace trivium {

        inline std::vector<bool> keystream_trivium_for_ASCII(const std::vector<bool> &message_in_bit) {
            std::bitset<93> a;
            std::bitset<84> b;
            std::bitset<111> c;
            std::bitset<80> iv_trivium;
            std::bitset<80> key;

            std::cout << "Die register ohne die key und iv bit: " << std::endl;
            std::cout << "A: " << a << " Länge: " << a.size() << std::endl;
            std::cout << "B: " << b << " Länge: " << b.size() << std::endl;
            std::cout << "C: " << c << " Länge: " << c.size() << std::endl;
            std::cout << "" << std::endl;

            std::vector<bool> keystream;
            keystream.resize(message_in_bit.size());

            for (auto i = 0; i < iv_trivium.size(); i++) {
                iv_trivium[i] = real_random_numbers();
            }
            for (auto i = 0; i < key.size(); i++) {
                key[i] = real_random_numbers();
            }
            std::cout << "IV: " << iv_trivium << " länge: "<< iv_trivium.size() << std::endl;
            std::cout << "KEY: " << key << " länge: "<< key.size() << std::endl;
            std::cout << "" << std::endl;

            for (auto i = 79; i >= 0; i--) {
                a[i + 13] = iv_trivium[i];
            }
            std::cout << "Der gefüllte a mit den iv: " << a << " länge: " << a.size() <<std::endl;

            for (auto i = 79; i >= 0; i--) {
                b[i+ +4] = key[i];
            }
            std::cout << "Der gefüllte b mit den key: " << b << " Länge: " << b.size() <<std::endl;
            //C:
            c[0]= true;
            c[1]= true;
            c[2]= true;
            std::cout << "Der gefüllte c mit den einsen: " << c << " länge: " << c.size() <<std::endl;
            std::cout << "" << std::endl;

            for (auto i =0; i < 1152; i++) {
                
                bool betweenA = a[66]^a[93];
                bool betweenB = b[69]^b[84] ;
                bool betweenC = c[66]^c[111];

                bool insertB = betweenA ^ (a[91]&a[92]) ^ b[78];
                bool insertC = betweenB ^ (b[82]&b[83]) ^ c[87];
                bool insertA = betweenC ^ (c[108]&c[110]) ^ a[69];

                a >>=1;
                b >>=1;
                c >>=1;

                a[92] = insertA;
                b[83] = insertB;
                c[110] = insertC;
            }

            for (auto i = 0; i < keystream.size(); i++) {
                bool betweenA = a[66]^a[93];
                bool betweenB = b[69]^b[84];
                bool betweenC = c[66]^c[111];

                bool insertB = betweenA ^ (a[91]&a[92]) ^ b[78];
                bool insertC = betweenB ^ (b[82]&b[83]) ^ c[87];
                bool insertA = betweenC ^ (c[108]&c[110]) ^ a[69];

                a >>=1;
                b >>=1;
                c >>=1;

                a[92] = insertA;
                b[83] = insertB;
                c[110] = insertC;

                keystream[i] = betweenA ^ betweenB ^betweenC;
            }

            return keystream;
        }

        inline void entschlusseln_trivium_for_ASII(std::vector<bool> &keystream_trivium, std::vector<std::bitset<8>> &message_in_bit) {
            //Coming Soon

        }

    }
}
