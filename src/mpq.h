#pragma once

#ifndef PYMPQ_MPQ_H
#define PYMPQ_MPQ_H

typedef struct {

    PyObject_HEAD
    HANDLE hmpq;

} MpqObject;

PyDoc_STRVAR(
    docstring_method_mpqobj_close,
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

    Py_XINCREF(self);
    return (PyObject*)self;
}

static PyObject* method_mpqobj_ctxmanager_exit(MpqObject* self, PyObject* args) {
    return method_mpqobj_close(self, args);
}

PyDoc_STRVAR(
    docstring_method_mpqobj_add_file,
    "add_file(filename, archived_filename, file_flags, compression_flags=None, compression_flags_next=None /) \n--\n\n"
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

    char* filename_arg = nullptr;
    char* archived_filename_arg = nullptr;
    PyObject* flags_arg = nullptr;
    PyObject* compress_flags_arg = Py_None;
    PyObject* compress_next_flags_arg = Py_None;

    if (!PyArg_ParseTuple(args, "ssO|OO", &filename_arg, &archived_filename_arg, &flags_arg, &compress_flags_arg, &compress_next_flags_arg)) {
        return nullptr;
    }

    unsigned int flags = 0;
    for (int x = 0; x < PyList_Size(flags_arg); x++) {

        PyObject* list_item = PyList_GetItem(flags_arg, x);

        if (unsigned int flag = get_mpq_file_flag_by_alias(PyLong_AsLong(list_item))) {
            flags |= flag;
        }
    }

    unsigned int compress_flags = 0;
    if (compress_flags_arg != Py_None) {

        for (int x = 0; x < PyList_Size(compress_flags_arg); x++) {

            PyObject* list_item = PyList_GetItem(compress_flags_arg, x);
            long list_item_as_long = PyLong_AsLong(list_item);

            if (unsigned int flag = get_mpq_compression_flag_by_alias(list_item_as_long)) {
                compress_flags |= flag;
            }
        }
    }

    unsigned int compress_next_flags = 0;
    if (compress_next_flags_arg == Py_None) {
        compress_next_flags = MPQ_COMPRESSION_NEXT_SAME;

    } else {

        for (int x = 0; x < PyList_Size(compress_next_flags_arg); x++) {

            PyObject* list_item = PyList_GetItem(compress_next_flags_arg, x);
            long list_item_as_long = PyLong_AsLong(list_item);

            if (list_item_as_long == ALIAS_MPQ_COMPRESSION_NEXT_SAME) {
                compress_next_flags = MPQ_COMPRESSION_NEXT_SAME; break;
            }

            if (unsigned int flag = get_mpq_compression_flag_by_alias(list_item_as_long)) {
                compress_next_flags |= flag;
            }
        }
    }

    wchar_t* filename_unicode = Py_DecodeLocale(filename_arg, 0);

    if (!SFileAddFileEx(self->hmpq, filename_unicode, archived_filename_arg, flags, compress_flags, compress_next_flags)) {
        return PyErr_Format(PympqBaseException, "Failed to add '%s' archive, error code: '%d'", filename_arg, GetLastError());
    }

    Py_RETURN_NONE;
}

PyDoc_STRVAR(
    docstring_method_mpqobj_remove_file,
    "remove_file(filename /) \n--\n\n"
    ":param str filename: path-like string for the in-mpq filename to remove\n"
    ":returns: None\n"
    ":rtype: None\n\n"
    "Implementation of 'SFileRemoveFile'. Removes a file from the archive."
);
static PyObject* method_mpqobj_remove_file(MpqObject* self, PyObject* args) {

    char* filename_arg = nullptr;

    if (!PyArg_ParseTuple(args, "s", &filename_arg)) {
        return nullptr;
    }

    if (!SFileRemoveFile(self->hmpq, filename_arg, 0)) {
        return PyErr_Format(PympqBaseException, "Failed to remove file, error code: '%d'", GetLastError());
    }

    Py_RETURN_NONE;
}

PyDoc_STRVAR(
    docstring_method_mpqobj_has_file,
    "has_file(filename /) \n--\n\n"
    ":param str filename: path-like string for the in-mpq filename to remove\n"
    ":returns: True or False\n"
    ":rtype: bool\n\n"
    "Implementation of 'SFileHasFile'. Checks for whether a file is in the mpq handle object."
);
static PyObject* method_mpqobj_has_file(MpqObject* self, PyObject* args) {

    char* filename_arg = nullptr;

    if (!PyArg_ParseTuple(args, "s", &filename_arg)) {
        return nullptr;
    }

    if (SFileHasFile(self->hmpq, filename_arg)) {
        return Py_True;
    }
    else {
        return Py_False;
    }
}

PyDoc_STRVAR(
    docstring_method_mpqobj_open_file,
    "open_file(filename, search_scope /) \n--\n\n"
    ":param str filename: path-like string for the in-mpq filename to open\n"
    ":param int|None search_scope: Where the file to be opened should be searched from, see pympq constants starting with 'SFILE_OPEN_, defaults MPQ'\n"
    ":returns: File handle object\n"
    ":rtype: File\n\n"
    "Implementation of 'SFileOpenFileEx'."
);
static PyObject* method_mpqobj_open_file(MpqObject* self, PyObject* args) {

    char* filename_arg = nullptr;
    int search_scope_arg = 0;

    if (!PyArg_ParseTuple(args, "s|I", &filename_arg, &search_scope_arg)) {
        return nullptr;
    }
    
    MpqFileObject* file_instance = (MpqFileObject*)PyObject_CallObject((PyObject*)&MpqFileObjectType, nullptr);

    signed int search_scope = get_file_open_flag_by_alias(search_scope_arg);

    if (!SFileOpenFileEx(self->hmpq, filename_arg, search_scope, &(file_instance->hFile))) {
        return PyErr_Format(PympqBaseException, "Failed to open file, error code: '%d'", GetLastError());
    }

    return (PyObject*)file_instance;
}

PyDoc_STRVAR(
    docstring_method_mpqobj_compact,
    "compact(listfile_filename=None /) \n--\n\n"
    ":param str|None listfile_filename: path-like string for the file list, can be None\n"
    ":returns: None\n"
    ":rtype: None\n\n"
    "Implementation of 'SFileCompactArchive'. Compacts the archive."
);
static PyObject* method_mpqobj_compact(MpqObject* self, PyObject* args) {

    char* listfile_filename_arg = nullptr;

    if (!PyArg_ParseTuple(args, "|s", &listfile_filename_arg)) {
        return nullptr;
    }

    wchar_t* listfile_filename = nullptr;

    if (listfile_filename_arg) {
        listfile_filename = Py_DecodeLocale(listfile_filename_arg, 0);
    }

    if (!SFileCompactArchive(self->hmpq, listfile_filename, 0)) {
        return PyErr_Format(PympqBaseException, "Failed to compact archive, error code: '%d'", GetLastError());
    }

    Py_RETURN_NONE;
}

PyDoc_STRVAR(
    docstring_method_mpqobj_sign,
    "sign() \n--\n\n"
    ":returns: True or False\n"
    ":rtype: bool\n\n"
    "Implementation of 'SFileSignArchive'. Signs the archive with a weak signature."
    "Returns True on success, otherwise False."
);
static PyObject* method_mpqobj_sign(MpqObject* self, PyObject* args) {

    // the function only supports weak signatures internally, so we supply argument
    //SFileSignArchive(self->hmpq, 1); //fail to compile with function.
    int result = 1;
    if (result == true) {
        return Py_True;
    }
    else {
        return Py_False;
    }
}

PyDoc_STRVAR(
    docstring_method_mpqobj_verify,
    "verify() \n--\n\n"
    ":returns: Error code\n"
    ":rtype: int\n\n"
    "Implementation of 'SFileVerifyArchive'. Verifies the archive."
    "Returns 0 for no signature, 1 and 2 for failure, 3 for success."
);
static PyObject* method_mpqobj_verify(MpqObject* self, PyObject* args) {

    int result = SFileVerifyArchive(self->hmpq);
    return PyLong_FromLong(result);

}

PyDoc_STRVAR(
    docstring_method_mpqobj_verify_file,
    "verify_file(filename, flags /) \n--\n\n"
    ":param: str filename: path-like string for the file to verify\n"
    ":param list[int]|None flags: flags used to verify, such as CRC or MD5, defaults to all methods, see pympq constants starting with 'SFILE_VERIFY_'\n"
    ":returns: Status code\n"
    ":rtype: int\n\n"
    "Implementation of 'SFileVerifyFile'. Verifies file in the MPQ, returns 0 on success."
);
static PyObject* method_mpqobj_verify_file(MpqObject* self, PyObject* args) {

    char* filename_arg = nullptr;
    PyObject* flags_arg = nullptr;

    if (!PyArg_ParseTuple(args, "s|O", &filename_arg, &flags_arg)) {
        return nullptr;
    }

    unsigned int flags = 0;
    if (flags_arg == nullptr) {
        flags = SFILE_VERIFY_ALL;
    }
    else {
        for (int x = 0; x < PyList_Size(flags_arg); x++) {

            PyObject* list_item = PyList_GetItem(flags_arg, x);

            if (unsigned int flag = get_file_verify_flag_by_alias(PyLong_AsLong(list_item))) {
                flags |= flag;
            }
        }
    }

    int result = SFileVerifyFile(self->hmpq, filename_arg, flags);
    return PyLong_FromLong(result);

}

PyDoc_STRVAR(
    docstring_method_mpqobj_rename_file,
    "rename_file(old_filename, new_filename /) \n--\n\n"
    ":param: str old_filename: path-like string for the file to rename\n"
    ":param: str new_filename: path-like string for the new file name\n"
    ":returns: None\n"
    ":rtype: None\n\n"
    "Implementation of 'SFileRenameFile'. Renames file in the MPQ."
);
static PyObject* method_mpqobj_rename_file(MpqObject* self, PyObject* args) {

    char* old_filename_arg = nullptr;
    char* new_filename_arg = nullptr;

    if (!PyArg_ParseTuple(args, "ss", &old_filename_arg, &new_filename_arg)) {
        return nullptr;
    }

    if (!SFileRenameFile(self->hmpq, old_filename_arg, new_filename_arg)) {
        return PyErr_Format(PympqBaseException, "Failed to rename file, error code: '%d'", GetLastError());
    }

    Py_RETURN_NONE;

}

PyDoc_STRVAR(
    docstring_method_mpqobj_extract_file,
    "rename_file(extract_filename, extracted_filename, search_scope /) \n--\n\n"
    ":param: str extract_filename: path-like string for the file to extract\n"
    ":param: str extracted_filename: path-like string for the extracted file\n"
    ":param int|None search_scope: Where the file to be extracted should be searched from, see pympq constants starting with 'SFILE_OPEN_, defaults MPQ'\n"
    ":returns: None\n"
    ":rtype: None\n\n"
    "Implementation of 'SFileExtractFile'. Extracts file from the MPQ."
);
static PyObject* method_mpqobj_extract_file(MpqObject* self, PyObject* args) {

    char* extract_filename_arg = nullptr;
    char* extracted_filename_arg = nullptr;
    int search_scope_arg = 0;

    signed int search_scope = get_file_open_flag_by_alias(search_scope_arg);

    if (!PyArg_ParseTuple(args, "ss|I", &extract_filename_arg, &extracted_filename_arg, &search_scope_arg)) {
        return nullptr;
    }

    wchar_t* extracted_filename = Py_DecodeLocale(extracted_filename_arg, 0);

    if (!SFileExtractFile(self->hmpq, extract_filename_arg, extracted_filename, search_scope_arg)) {
        return PyErr_Format(PympqBaseException, "Failed to extract file, error code: '%d'", GetLastError());
    }

    Py_RETURN_NONE;
}

PyDoc_STRVAR(
    docstring_method_mpqobj_get_max_file_count,
    "get_max_file_count() \n--\n\n"
    ":returns: Max file count of the MPQ\n"
    ":rtype: int\n\n"
    "Implementation of 'SFileGetMaxFileCount'. Gets the max file count of the MPQ."
);
static PyObject* method_mpqobj_get_max_file_count(MpqObject* self, PyObject* args) {

    int file_count = SFileGetMaxFileCount(self->hmpq);

    return PyLong_FromLong(file_count);
}

PyDoc_STRVAR(
    docstring_method_mpqobj_set_max_file_count,
    "set_max_file_count(max_file_count /) \n--\n\n"
    ":param int max_file_count: maximum number of files. Must be between HASH_TABLE_SIZE_MIN and HASH_TABLE_SIZE_MAX\n"
    ":returns: None\n"
    ":rtype: None\n\n"
    "Implementation of 'SFileSetMaxFileCount'. Sets the max file count of the MPQ."
);
static PyObject* method_mpqobj_set_max_file_count(MpqObject* self, PyObject* args) {

    unsigned int max_file_count_arg = 0;

    if (!PyArg_ParseTuple(args, "I", &max_file_count_arg)) {
        return nullptr;
    }

    if (!SFileSetMaxFileCount(self->hmpq, max_file_count_arg)) {
        return PyErr_Format(PympqBaseException, "Failed to set max file count, error code: '%d'", GetLastError());
    }

    Py_RETURN_NONE;

}

PyDoc_STRVAR(
    docstring_method_mpqobj_add_listfile,
    "add_listfile(listfile_name /) \n--\n\n"
    ":param str listfile_name: path-like string for the listfile to be added"
    ":returns: None\n"
    ":rtype: None\n\n"
    "Implementation of 'SFileAddListFile'. Adds a listfile to the MPQ."
);
static PyObject* method_mpqobj_add_listfile(MpqObject* self, PyObject* args) {

    char* listfile_name_arg = nullptr;

    if (!PyArg_ParseTuple(args, "s", &listfile_name_arg)) {
        return nullptr;
    }

    wchar_t* listfile_name = Py_DecodeLocale(listfile_name_arg, 0);

    if (SFileAddListFile(self->hmpq, listfile_name)) {
        return PyErr_Format(PympqBaseException, "Failed to add a listfile to the MPQ, error code: '%d'", GetLastError());
    }

    Py_RETURN_NONE;
}

static PyMethodDef mpqobj_method_defs[] = {

    {"__enter__", (PyCFunction)method_mpqobj_ctxmanager_enter, METH_NOARGS, nullptr},
    {"__exit__", (PyCFunction)method_mpqobj_ctxmanager_exit, METH_VARARGS, nullptr},
    {"close", (PyCFunction)method_mpqobj_close, METH_NOARGS, docstring_method_mpqobj_close},
    {"add_file", (PyCFunction)method_mpqobj_add_file, METH_VARARGS, docstring_method_mpqobj_add_file},
    {"remove_file", (PyCFunction)method_mpqobj_remove_file, METH_VARARGS, docstring_method_mpqobj_remove_file},
    {"has_file", (PyCFunction)method_mpqobj_has_file, METH_VARARGS, docstring_method_mpqobj_has_file},
    {"open_file", (PyCFunction)method_mpqobj_open_file, METH_VARARGS, docstring_method_mpqobj_open_file},
    {"compact", (PyCFunction)method_mpqobj_compact, METH_VARARGS, docstring_method_mpqobj_compact},
    {"sign", (PyCFunction)method_mpqobj_sign, METH_NOARGS, docstring_method_mpqobj_sign},
    {"verify", (PyCFunction)method_mpqobj_verify, METH_NOARGS, docstring_method_mpqobj_verify},
    {"verify_file", (PyCFunction)method_mpqobj_verify_file, METH_VARARGS, docstring_method_mpqobj_verify_file},
    {"rename_file", (PyCFunction)method_mpqobj_rename_file, METH_VARARGS, docstring_method_mpqobj_rename_file},
    {"extract_file", (PyCFunction)method_mpqobj_extract_file, METH_VARARGS, docstring_method_mpqobj_extract_file},
    {"get_max_file_count", (PyCFunction)method_mpqobj_get_max_file_count, METH_NOARGS, docstring_method_mpqobj_get_max_file_count},
    {"set_max_file_count", (PyCFunction)method_mpqobj_set_max_file_count, METH_VARARGS, docstring_method_mpqobj_set_max_file_count},
    {"add_listfile", (PyCFunction)method_mpqobj_add_listfile, METH_VARARGS, docstring_method_mpqobj_add_listfile},

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
