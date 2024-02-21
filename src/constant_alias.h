#pragma once

#ifndef PYMPQ_CONSTANT_ALIAS_H
#define PYMPQ_CONSTANT_ALIAS_H

#define ALIAS_MPQ_CREATE_LISTFILE 1
#define ALIAS_MPQ_CREATE_ATTRIBUTES 2
#define ALIAS_MPQ_CREATE_SIGNATURE 3
#define ALIAS_MPQ_CREATE_ARCHIVE_V1 4
#define ALIAS_MPQ_CREATE_ARCHIVE_V2 5
#define ALIAS_MPQ_CREATE_ARCHIVE_V3 6
#define ALIAS_MPQ_CREATE_ARCHIVE_V4 7

unsigned int get_mpq_create_flag_by_alias(long alias) {

    if (alias == ALIAS_MPQ_CREATE_LISTFILE) {
        return MPQ_CREATE_LISTFILE;
    }
    else if (alias == ALIAS_MPQ_CREATE_ATTRIBUTES) {
        return MPQ_CREATE_ATTRIBUTES;
    }
    else if (alias == ALIAS_MPQ_CREATE_SIGNATURE) {
        return MPQ_CREATE_SIGNATURE;
    }
    else if (alias == ALIAS_MPQ_CREATE_ARCHIVE_V1) {
        return MPQ_CREATE_ARCHIVE_V1;
    }
    else if (alias == ALIAS_MPQ_CREATE_ARCHIVE_V2) {
        return MPQ_CREATE_ARCHIVE_V2;
    }
    else if (alias == ALIAS_MPQ_CREATE_ARCHIVE_V3) {
        return MPQ_CREATE_ARCHIVE_V3;
    }
    else if (alias == ALIAS_MPQ_CREATE_ARCHIVE_V4) {
        return MPQ_CREATE_ARCHIVE_V4;
    }
    else {
        return 0;
    }
}

#define ALIAS_MPQ_FILE_IMPLODE 1
#define ALIAS_MPQ_FILE_COMPRESS 2
#define ALIAS_MPQ_FILE_ENCRYPTED 3
#define ALIAS_MPQ_FILE_FIX_KEY 4
#define ALIAS_MPQ_FILE_DELETE_MARKER 5
#define ALIAS_MPQ_FILE_SECTOR_CRC 6
#define ALIAS_MPQ_FILE_SINGLE_UNIT 7
#define ALIAS_MPQ_FILE_REPLACEEXISTING 8

unsigned int get_mpq_file_flag_by_alias(long alias) {

    if (alias == ALIAS_MPQ_FILE_IMPLODE) {
        return MPQ_FILE_IMPLODE;
    }
    else if (alias == ALIAS_MPQ_FILE_COMPRESS) {
        return MPQ_FILE_COMPRESS;
    }
    else if (alias == ALIAS_MPQ_FILE_ENCRYPTED) {
        return MPQ_FILE_ENCRYPTED;
    }
    else if (alias == ALIAS_MPQ_FILE_FIX_KEY) {
        return MPQ_FILE_FIX_KEY;
    }
    else if (alias == ALIAS_MPQ_FILE_DELETE_MARKER) {
        return MPQ_FILE_DELETE_MARKER;
    }
    else if (alias == ALIAS_MPQ_FILE_SECTOR_CRC) {
        return MPQ_FILE_SECTOR_CRC;
    }
    else if (alias == ALIAS_MPQ_FILE_SINGLE_UNIT) {
        return MPQ_FILE_SINGLE_UNIT;
    }
    else if (alias == ALIAS_MPQ_FILE_REPLACEEXISTING) {
        return MPQ_FILE_REPLACEEXISTING;
    }
    else {
        return 0;
    }
}

#define ALIAS_MPQ_COMPRESSION_HUFFMANN 1
#define ALIAS_MPQ_COMPRESSION_ZLIB 2
#define ALIAS_MPQ_COMPRESSION_PKWARE 3
#define ALIAS_MPQ_COMPRESSION_BZIP2 4
#define ALIAS_MPQ_COMPRESSION_SPARSE 5
#define ALIAS_MPQ_COMPRESSION_ADPCM_MONO 6
#define ALIAS_MPQ_COMPRESSION_ADPCM_STEREO 7
#define ALIAS_MPQ_COMPRESSION_LZMA 8
#define ALIAS_MPQ_COMPRESSION_NEXT_SAME 100

unsigned int get_mpq_compression_flag_by_alias(long alias) {

    if (alias == ALIAS_MPQ_COMPRESSION_HUFFMANN) {
        return MPQ_COMPRESSION_HUFFMANN;
    }
    else if (alias == ALIAS_MPQ_COMPRESSION_ZLIB) {
        return MPQ_COMPRESSION_ZLIB;
    }
    else if (alias == ALIAS_MPQ_COMPRESSION_PKWARE) {
        return MPQ_COMPRESSION_PKWARE;
    }
    else if (alias == ALIAS_MPQ_COMPRESSION_BZIP2) {
        return MPQ_COMPRESSION_BZIP2;
    }
    else if (alias == ALIAS_MPQ_COMPRESSION_SPARSE) {
        return MPQ_COMPRESSION_SPARSE;
    }
    else if (alias == ALIAS_MPQ_COMPRESSION_ADPCM_MONO) {
        return MPQ_COMPRESSION_ADPCM_MONO;
    }
    else if (alias == ALIAS_MPQ_COMPRESSION_ADPCM_STEREO) {
        return MPQ_COMPRESSION_ADPCM_STEREO;
    }
    else if (alias == ALIAS_MPQ_COMPRESSION_LZMA) {
        return MPQ_COMPRESSION_LZMA;
    }
    else {
        return 0;
    }
}

#endif