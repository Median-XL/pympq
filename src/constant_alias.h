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

#define ALIAS_BASE_PROVIDER_FILE 1
#define ALIAS_BASE_PROVIDER_MAP 2
#define ALIAS_BASE_PROVIDER_HTTP 3
#define ALIAS_BASE_PROVIDER_MASK 4

#define ALIAS_STREAM_PROVIDER_FLAT 100
#define ALIAS_STREAM_PROVIDER_PARTIAL 101
#define ALIAS_STREAM_PROVIDER_MPQE 102
#define ALIAS_STREAM_PROVIDER_BLOCK4 103
#define ALIAS_STREAM_PROVIDER_MASK 104
#define ALIAS_STREAM_FLAG_READ_ONLY 105
#define ALIAS_STREAM_FLAG_WRITE_SHARE 106
#define ALIAS_STREAM_FLAG_USE_BITMAP 107
#define ALIAS_STREAM_OPTIONS_MASK 108
#define ALIAS_STREAM_PROVIDERS_MASK 109
#define ALIAS_STREAM_FLAGS_MASK 110

#define ALIAS_MPQ_OPEN_NO_LISTFILE 1000
#define ALIAS_MPQ_OPEN_NO_ATTRIBUTES 1001
#define ALIAS_MPQ_OPEN_NO_HEADER_SEARCH 1002
#define ALIAS_MPQ_OPEN_FORCE_MPQ_V1 1003
#define ALIAS_MPQ_OPEN_CHECK_SECTOR_CRC 1004
#define ALIAS_MPQ_OPEN_PATCH 1005
#define ALIAS_MPQ_OPEN_FORCE_LISTFILE 1006
#define ALIAS_MPQ_OPEN_READ_ONLY 1007

unsigned int get_mpq_open_flag_by_alias(long alias) {

    switch (alias) {
    case ALIAS_BASE_PROVIDER_FILE: return BASE_PROVIDER_FILE;
    case ALIAS_BASE_PROVIDER_MAP: return BASE_PROVIDER_MAP;
    case ALIAS_BASE_PROVIDER_HTTP: return BASE_PROVIDER_HTTP;
    case ALIAS_BASE_PROVIDER_MASK: return BASE_PROVIDER_MASK;
    case ALIAS_STREAM_PROVIDER_FLAT: return STREAM_PROVIDER_FLAT;
    case ALIAS_STREAM_PROVIDER_PARTIAL: return STREAM_PROVIDER_PARTIAL;
    case ALIAS_STREAM_PROVIDER_MPQE: return STREAM_PROVIDER_MPQE;
    case ALIAS_STREAM_PROVIDER_BLOCK4: return STREAM_PROVIDER_BLOCK4;
    case ALIAS_STREAM_PROVIDER_MASK: return STREAM_PROVIDER_MASK;
    case ALIAS_STREAM_FLAG_READ_ONLY: return STREAM_FLAG_READ_ONLY;
    case ALIAS_STREAM_FLAG_WRITE_SHARE: return STREAM_FLAG_WRITE_SHARE;
    case ALIAS_STREAM_OPTIONS_MASK: return STREAM_OPTIONS_MASK;
    case ALIAS_STREAM_PROVIDERS_MASK: return STREAM_PROVIDERS_MASK;
    case ALIAS_STREAM_FLAGS_MASK: return STREAM_FLAGS_MASK;
    case ALIAS_MPQ_OPEN_NO_LISTFILE: return MPQ_OPEN_NO_LISTFILE;
    case ALIAS_MPQ_OPEN_NO_ATTRIBUTES: return MPQ_OPEN_NO_ATTRIBUTES;
    case ALIAS_MPQ_OPEN_NO_HEADER_SEARCH: return MPQ_OPEN_NO_HEADER_SEARCH;
    case ALIAS_MPQ_OPEN_FORCE_MPQ_V1: return MPQ_OPEN_FORCE_MPQ_V1;
    case ALIAS_MPQ_OPEN_CHECK_SECTOR_CRC: return MPQ_OPEN_CHECK_SECTOR_CRC;
    case ALIAS_MPQ_OPEN_PATCH: return MPQ_OPEN_PATCH;
    case ALIAS_MPQ_OPEN_FORCE_LISTFILE: return MPQ_OPEN_FORCE_LISTFILE;
    case ALIAS_MPQ_OPEN_READ_ONLY: return MPQ_OPEN_READ_ONLY;
    default: return 0;
    }

}

#define ALIAS_SFILE_OPEN_FROM_MPQ 1
#define ALIAS_SFILE_OPEN_CHECK_EXISTS 2
#define ALIAS_SFILE_OPEN_LOCAL_FILE 3

signed int get_file_open_flag_by_alias(int alias) {
    
    if (alias == ALIAS_SFILE_OPEN_CHECK_EXISTS) {
        return SFILE_OPEN_CHECK_EXISTS;
    }
    else if (alias == ALIAS_SFILE_OPEN_LOCAL_FILE) {
        return SFILE_OPEN_LOCAL_FILE;
    }
    else {
        return SFILE_OPEN_FROM_MPQ;
    }
}

#endif