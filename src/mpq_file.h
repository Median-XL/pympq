#pragma once

#ifndef PYMPQ_FILE_H
#define PYMPQ_FILE_H

typedef struct {
    
    PyObject_HEAD
    HANDLE hFile;

} MpqFileObject;

PyDoc_STRVAR(
    docstring_method_fileobj_close,
    "close() \n--\n\n"
    ":returns: None\n"
    ":rtype: None\n\n"
    "Implementation of 'SFileCloseFile'. Closes an opened File handle object."
);
static PyObject* method_fileobj_close(MpqFileObject* self, PyObject* args) {

    if (!SFileCloseFile(self->hFile)) {
        return PyErr_Format(PympqBaseException, "Failed to close file, error code: '%d'", GetLastError());
    }

    Py_RETURN_NONE;
}

static PyObject* method_fileobj_ctxmanager_enter(MpqFileObject* self, PyObject* args) {

    Py_XINCREF(self);
    return (PyObject*)self;
}

static PyObject* method_fileobj_ctxmanager_exit(MpqFileObject* self, PyObject* args) {
    return method_fileobj_close(self, args);
}


PyDoc_STRVAR(
    docstring_method_fileobj_get_name,
    "get_name() \n--\n\n"
    ":returns: Name of file\n"
    ":rtype: Str\n\n"
    "Implementation of 'SFileGetFileName'. Gets name of file handle object."
);
static PyObject* method_fileobj_get_name(MpqFileObject* self, PyObject* args) {

    char buffer[MAX_PATH];
    if (!SFileGetFileName(self->hFile, buffer)) {
        return PyErr_Format(PympqBaseException, "Failed to get file name, error code: '%d'", GetLastError());
    }

    return PyUnicode_FromString(buffer);
}

PyDoc_STRVAR(
    docstring_method_fileobj_get_size,
    "get_size() \n--\n\n"
    ":returns: Size of file in bytes\n"
    ":rtype: int\n\n"
    "Implementation of 'SFileGetFileSize'. Gets size of file."
);
static PyObject* method_fileobj_get_size(MpqFileObject* self, PyObject* args) {

    int result = SFileGetFileSize(self->hFile, 0);
    if (result == SFILE_INVALID_SIZE) {
        return PyErr_Format(PympqBaseException, "Failed to get file size, error code: '%d'", GetLastError());
    }

    return PyLong_FromLong(result);
}

static PyMethodDef fileobj_method_defs[] = {

    {"__enter__", (PyCFunction)method_fileobj_ctxmanager_enter, METH_NOARGS, nullptr},
    {"__exit__", (PyCFunction)method_fileobj_ctxmanager_exit, METH_VARARGS, nullptr},
    {"close", (PyCFunction)method_fileobj_close, METH_NOARGS, docstring_method_fileobj_close},
    {"get_name", (PyCFunction)method_fileobj_get_name, METH_NOARGS, docstring_method_fileobj_get_name},
    {"get_size", (PyCFunction)method_fileobj_get_size, METH_NOARGS, docstring_method_fileobj_get_size},
};

static PyTypeObject MpqFileObjectType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pympq.MpqFile",                   /* tp_name */
    sizeof(MpqFileObject),             /* tp_basicsize */
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
    PyDoc_STR("File handle"),       /* tp_doc */
    0,                              /* tp_traverse */
    0,                              /* tp_clear */
    0,                              /* tp_richcompare */
    0,                              /* tp_weaklistoffset */
    0,                              /* tp_iter */
    0,                              /* tp_iternext */
    fileobj_method_defs,            /* tp_methods */
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