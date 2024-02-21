#pragma once

#ifndef PYMPQ_MPQ_H
#define PYMPQ_MPQ_H

typedef struct {

    PyObject_HEAD
    HANDLE hmpq;

} MpqObject;

PyDoc_STRVAR(
    doctsring_method_mpqobj_close,
    "close() \n--\n\n"
    ":returns: None\n"
    ":rtype: None\n\n"
    "Implementation of 'SFileCloseArchive'. Closes an opened Mpq handle object."
);
static PyObject* method_mpqobj_close(MpqObject* self, PyObject* args) {

    if (!SFileCloseArchive(self->hmpq)) {
        return PyErr_Format(PympqBaseException, "Failed to close archive, error code: '%d'", GetLastError());
    }

    Py_RETURN_NONE;
}

static PyObject* method_mpqobj_ctxmanager_enter(MpqObject* self, PyObject* args) {
    return (PyObject*)self;
}

static PyObject* method_mpqobj_ctxmanager_exit(MpqObject* self, PyObject* args) {
    return method_mpqobj_close(self, args);
}

PyDoc_STRVAR(
    doctsring_method_mpqobj_add_file,
    "add_file(filename, archived_filename, file_flags, compression_flags, compression_flags_next=None /) \n--\n\n"
    ":param str filename: path-like string for the file to add on disk\n"
    ":param str archived_filename: path-like string for the file name in the mpq\n"
    ":param list[int] file_flags: file flags, see pympq constants starting with 'MPQ_FILE_'\n"
    ":param list[int] compression_flags: file compression flags for the first block of the file, see pympq constants starting with 'MPQ_COMPRESSION_'\n"
    ":param list[int]|None compression_flags_next: file compression flags for rest of the file, use 'MPQ_COMPRESSION_NEXT_SAME' to use same flags as provided for the first block. Setting this parameter to None will default to 'MPQ_COMPRESSION_NEXT_SAME'\n"
    ":returns: None\n"
    ":rtype: None\n\n"
    "Implementation of 'SFileAddFileEx'. Adds file to the mpq archive."
);
static PyObject* method_mpqobj_add_file(MpqObject* self, PyObject* args) {

    char* filename = nullptr;
    char* archived_name = nullptr;
    PyObject* flags = nullptr;
    PyObject* compress_flags = nullptr;
    PyObject* compress_next_flags = Py_None;

    if (!PyArg_ParseTuple(args, "ssOO|O", &filename, &archived_name, &flags, &compress_flags, &compress_next_flags)) {
        return nullptr;
    }

    unsigned int combined_flags = 0;
    for (int x = 0; x < PyList_Size(flags); x++) {

        PyObject* list_item = PyList_GetItem(flags, x);

        if (unsigned int flag = get_mpq_file_flag_by_alias(PyLong_AsLong(list_item))) {
            combined_flags |= flag;
        }
    }

    unsigned int combined_compress_flags = 0;
    for (int x = 0; x < PyList_Size(compress_flags); x++) {

        PyObject* list_item = PyList_GetItem(compress_flags, x);
        long list_item_as_long = PyLong_AsLong(list_item);

        if (unsigned int flag = get_mpq_compression_flag_by_alias(list_item_as_long)) {
            combined_compress_flags |= flag;
        }
    }

    unsigned int combined_compress_next_flags = 0;

    if (compress_next_flags == Py_None) {
        combined_compress_next_flags = MPQ_COMPRESSION_NEXT_SAME;

    } else {

        for (int x = 0; x < PyList_Size(compress_next_flags); x++) {

            PyObject* list_item = PyList_GetItem(compress_next_flags, x);
            long list_item_as_long = PyLong_AsLong(list_item);

            if (list_item_as_long == ALIAS_MPQ_COMPRESSION_NEXT_SAME) {
                combined_compress_next_flags = MPQ_COMPRESSION_NEXT_SAME; break;
            }

            if (unsigned int flag = get_mpq_compression_flag_by_alias(list_item_as_long)) {
                combined_compress_next_flags |= flag;
            }
        }
    }

    wchar_t* filename_unicode = Py_DecodeLocale(filename, 0);

    if (!SFileAddFileEx(self->hmpq, filename_unicode, archived_name, combined_flags, combined_compress_flags, combined_compress_next_flags)) {
        return PyErr_Format(PympqBaseException, "Failed to add '%s' archive, error code: '%d'", filename, GetLastError());
    }

    Py_RETURN_NONE;
}

PyDoc_STRVAR(
    doctsring_method_mpqobj_compact,
    "compact(listfile_filename=None /) \n--\n\n"
    ":param str|None listfile_filename: path-like string for the file list, can be None\n"
    ":returns: None\n"
    ":rtype: None\n\n"
    "Implementation of 'SFileCompactArchive'. Compacts the archive."
);
static PyObject* method_mpqobj_compact(MpqObject* self, PyObject* args) {

    char* listfile_filename_or_none = nullptr;

    if (!PyArg_ParseTuple(args, "|s", &listfile_filename_or_none)) {
        return nullptr;
    }

    wchar_t* listfile_filename = nullptr;

    if (listfile_filename_or_none) {
        listfile_filename = Py_DecodeLocale(listfile_filename_or_none, 0);
    }

    if (!SFileCompactArchive(self->hmpq, listfile_filename, 0)) {
        return PyErr_Format(PympqBaseException, "Failed to compact archive, error code: '%d'", GetLastError());
    }

    Py_RETURN_NONE;
}

static PyMethodDef mpqobj_method_defs[] = {

    {"__enter__", (PyCFunction)method_mpqobj_ctxmanager_enter, METH_NOARGS, nullptr},
    {"__exit__", (PyCFunction)method_mpqobj_ctxmanager_exit, METH_VARARGS, nullptr},
    {"close", (PyCFunction)method_mpqobj_close, METH_NOARGS, doctsring_method_mpqobj_close},
    {"add_file", (PyCFunction)method_mpqobj_add_file, METH_VARARGS, doctsring_method_mpqobj_add_file},
    {"compact", (PyCFunction)method_mpqobj_compact, METH_VARARGS, doctsring_method_mpqobj_compact},

    {nullptr, nullptr, 0, nullptr},
};

static PyTypeObject MpqObjectType = {

    PyVarObject_HEAD_INIT(NULL, 0)
    "pympq.Mpq",                    /* tp_name */
    sizeof(MpqObject),              /* tp_basicsize */
    0,                              /* tp_itemsize */
    0,                              /* tp_dealloc */
    0,                              /* tp_vectorcall_offset */
    0,                              /* tp_getattr */
    0,                              /* tp_setattr */
    0,                              /* tp_as_async */
    0,                              /* tp_repr */
    0,                              /* tp_as_number */
    0,                              /* tp_as_sequence */
    0,                              /* tp_as_mapping */
    0,                              /* tp_hash */
    0,                              /* tp_call */
    0,                              /* tp_str */
    0,                              /* tp_getattro */
    0,                              /* tp_setattro */
    0,                              /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,             /* tp_flags */
    PyDoc_STR("MPQ handle"),        /* tp_doc */
    0,                              /* tp_traverse */
    0,                              /* tp_clear */
    0,                              /* tp_richcompare */
    0,                              /* tp_weaklistoffset */
    0,                              /* tp_iter */
    0,                              /* tp_iternext */
    mpqobj_method_defs,             /* tp_methods */
    0,                              /* tp_members */
    0,                              /* tp_getset */
    0,                              /* tp_base */
    0,                              /* tp_dict */
    0,                              /* tp_descr_get */
    0,                              /* tp_descr_set */
    0,                              /* tp_dictoffset */
    0,                              /* tp_init */
    0,                              /* tp_alloc */
    PyType_GenericNew,              /* tp_new */
};

#endif
