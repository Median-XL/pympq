#include <Python.h>
#include <structmember.h>
#include "StormLib.h"

#include "exception.h"
#include "constant_alias.h"
#include "mpq.h"
#include "file.h"

PyDoc_STRVAR(
    doctsring_method_create_archive,
    "create_archive(mpq_filename, create_flags, max_file_count, /) \n--\n\n"
    ":param str mpq_filename: path-like string for the mpq\n"
    ":param list[int] create_flags: list of flags for creation, see pympq constants starting with 'MPQ_CREATE_'\n"
    ":param int max_file_count: maximum number of files\n"
    ":returns: Mpq handle object\n"
    ":rtype: Mpq\n\n"
    "Implementation of 'SFileCreateArchive'. The returned Mpq object has to be closed by "
    "calling its .close() method or can be used as a context manager for automatic closing"
);
PyObject* method_create_archive(PyObject* self, PyObject* args) {

    char* mpq_filename_arg = nullptr;
    PyObject* flags_arg = nullptr;
    unsigned int max_file_count_arg = 0;

    if (!PyArg_ParseTuple(args, "sOI", &mpq_filename_arg, &flags_arg, &max_file_count_arg)) {
        return nullptr;
    }

    unsigned int flags = 0;
    for (int x = 0; x < PyList_Size(flags_arg); x++) {

        PyObject* list_item = PyList_GetItem(flags_arg, x);

        if (unsigned int flag = get_mpq_create_flag_by_alias(PyLong_AsLong(list_item))) {
            flags |= flag;
        }
    }

    wchar_t* mpq_filename = Py_DecodeLocale(mpq_filename_arg, 0);
    MpqObject* mpq_instance = (MpqObject*)PyObject_CallObject((PyObject*)&MpqObjectType, nullptr);

    if (!SFileCreateArchive(mpq_filename, flags, max_file_count_arg, &(mpq_instance->hmpq))) {
        return PyErr_Format(PympqBaseException, "Failed to create archive, error code: '%d'", GetLastError());
    }

    return (PyObject*)mpq_instance;
}

PyDoc_STRVAR(
    docstring_method_open_archive,
    "open_archive(mpq_filename, flags /) \n--\n\n"
    ":param str mpq_filename: path-like string for the mpq\n"
    ":param list[int]|None open_flags: list of flags for creation, see pympq constants starting with 'MPQ_CREATE_'\n"
    ":returns: Mpq handle object\n"
    ":rtype: Mpq\n\n"
    "Implementation of 'SFileOpenArchive'. The returned Mpq object has to be closed by "
    "calling its .close() method or can be used as a context manager for automatic closing"
);
PyObject* method_open_archive(PyObject* self, PyObject* args) {

    char* mpq_filename_arg = nullptr;
    PyObject* open_flags_arg = Py_None;

    if (!PyArg_ParseTuple(args, "s|O", &mpq_filename_arg, &open_flags_arg)) {
        return nullptr;
    }

    wchar_t* mpq_filename = Py_DecodeLocale(mpq_filename_arg, 0);
    MpqObject* mpq_instance = (MpqObject*)PyObject_CallObject((PyObject*)&MpqObjectType, nullptr);

    unsigned int open_flags = 0;
    if (open_flags_arg == Py_None) {
        open_flags = 0;
    }
    else {
        for (int x = 0; x < PyList_Size(open_flags_arg); x++) {

            PyObject* list_item = PyList_GetItem(open_flags_arg, x);
            long list_item_as_long = PyLong_AsLong(list_item);

            if (unsigned int flag = get_mpq_open_flag_by_alias(list_item_as_long)) {
                open_flags |= flag;
            }
        }
    }

    // priority is deprecated
    if (!SFileOpenArchive(mpq_filename, 0, 0, &(mpq_instance->hmpq))) {
        return PyErr_Format(PympqBaseException, "Failed to open archive, error code: '%d'", GetLastError());
    }

    return (PyObject*)mpq_instance;
}

static PyMethodDef pympq_method_defs[] = {

    {"create_archive", method_create_archive, METH_VARARGS, doctsring_method_create_archive},
    {"open_archive", method_open_archive, METH_VARARGS, docstring_method_open_archive},

    {nullptr, nullptr, 0, nullptr},
};

static struct PyModuleDef pympq_module_def = {
    PyModuleDef_HEAD_INIT,
    "pympq",
    "python implementation of the stormlib API",
    -1,
    pympq_method_defs,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
};

PyMODINIT_FUNC PyInit_pympq(void) {

    PyObject* pympq_module = PyModule_Create(&pympq_module_def);

    if (PyType_Ready(&MpqObjectType) < 0) {

        Py_DECREF(pympq_module);
        return nullptr;
    }

    PyModule_AddIntConstant(pympq_module, "MPQ_CREATE_LISTFILE", ALIAS_MPQ_CREATE_LISTFILE);
    PyModule_AddIntConstant(pympq_module, "MPQ_CREATE_ATTRIBUTES", ALIAS_MPQ_CREATE_ATTRIBUTES);
    PyModule_AddIntConstant(pympq_module, "MPQ_CREATE_SIGNATURE", ALIAS_MPQ_CREATE_SIGNATURE);
    PyModule_AddIntConstant(pympq_module, "MPQ_CREATE_ARCHIVE_V1", ALIAS_MPQ_CREATE_ARCHIVE_V1);
    PyModule_AddIntConstant(pympq_module, "MPQ_CREATE_ARCHIVE_V2", ALIAS_MPQ_CREATE_ARCHIVE_V2);
    PyModule_AddIntConstant(pympq_module, "MPQ_CREATE_ARCHIVE_V3", ALIAS_MPQ_CREATE_ARCHIVE_V3);
    PyModule_AddIntConstant(pympq_module, "MPQ_CREATE_ARCHIVE_V4", ALIAS_MPQ_CREATE_ARCHIVE_V4);

    PyModule_AddIntConstant(pympq_module, "MPQ_FILE_IMPLODE", ALIAS_MPQ_FILE_IMPLODE);
    PyModule_AddIntConstant(pympq_module, "MPQ_FILE_COMPRESS", ALIAS_MPQ_FILE_COMPRESS);
    PyModule_AddIntConstant(pympq_module, "MPQ_FILE_ENCRYPTED", ALIAS_MPQ_FILE_ENCRYPTED);
    PyModule_AddIntConstant(pympq_module, "MPQ_FILE_FIX_KEY", ALIAS_MPQ_FILE_FIX_KEY);
    PyModule_AddIntConstant(pympq_module, "MPQ_FILE_DELETE_MARKER", ALIAS_MPQ_FILE_DELETE_MARKER);
    PyModule_AddIntConstant(pympq_module, "MPQ_FILE_SECTOR_CRC", ALIAS_MPQ_FILE_SECTOR_CRC);
    PyModule_AddIntConstant(pympq_module, "MPQ_FILE_SINGLE_UNIT", ALIAS_MPQ_FILE_SINGLE_UNIT);
    PyModule_AddIntConstant(pympq_module, "MPQ_FILE_REPLACEEXISTING", ALIAS_MPQ_FILE_REPLACEEXISTING);

    PyModule_AddIntConstant(pympq_module, "MPQ_COMPRESSION_HUFFMANN", ALIAS_MPQ_COMPRESSION_HUFFMANN);
    PyModule_AddIntConstant(pympq_module, "MPQ_COMPRESSION_ZLIB", ALIAS_MPQ_COMPRESSION_ZLIB);
    PyModule_AddIntConstant(pympq_module, "MPQ_COMPRESSION_PKWARE", ALIAS_MPQ_COMPRESSION_PKWARE);
    PyModule_AddIntConstant(pympq_module, "MPQ_COMPRESSION_BZIP2", ALIAS_MPQ_COMPRESSION_BZIP2);
    PyModule_AddIntConstant(pympq_module, "MPQ_COMPRESSION_SPARSE", ALIAS_MPQ_COMPRESSION_SPARSE);
    PyModule_AddIntConstant(pympq_module, "MPQ_COMPRESSION_ADPCM_MONO", ALIAS_MPQ_COMPRESSION_ADPCM_MONO);
    PyModule_AddIntConstant(pympq_module, "MPQ_COMPRESSION_ADPCM_STEREO", ALIAS_MPQ_COMPRESSION_ADPCM_STEREO);
    PyModule_AddIntConstant(pympq_module, "MPQ_COMPRESSION_LZMA", ALIAS_MPQ_COMPRESSION_LZMA);
    PyModule_AddIntConstant(pympq_module, "MPQ_COMPRESSION_NEXT_SAME", ALIAS_MPQ_COMPRESSION_NEXT_SAME);

    PympqBaseException = PyErr_NewException("pympq.MpqException", PyExc_Exception, nullptr);
    PyModule_AddObject(pympq_module, "MpqException", PympqBaseException);

    Py_INCREF(&MpqObjectType);
    if (PyModule_AddObject(pympq_module, "Mpq", (PyObject*)&MpqObjectType) < 0) {

        Py_DECREF(&MpqObjectType);
        Py_DECREF(pympq_module);

        return nullptr;
    }

    return pympq_module;
}
