/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:32:50 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:21:43 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/printf_internal.h"

const char	*_ft_str_errorname(int error)
{
	return ((const char *[]){
		"0", "EPERM", "ENOENT", "ESRCH", "EINTR", "EIO", "ENXIO", "E2BIG",
		"ENOEXEC", "EBADF", "ECHILD", "EAGAIN", "ENOMEM", "EACCES", "EFAULT",
		"ENOTBLK", "EBUSY", "EEXIST", "EXDEV", "ENODEV", "ENOTDIR", "EISDIR",
		"EINVAL", "ENFILE", "EMFILE", "ENOTTY", "ETXTBSY", "EFBIG", "ENOSPC",
		"ESPIPE", "EROFS", "EMLINK", "EPIPE", "EDOM", "ERANGE", "EDEADLK",
		"ENAMETOOLONG", "ENOLCK", "ENOSYS", "ENOTEMPTY", "ELOOP", "EWOULDBLOCK",
		"ENOMSG", "EIDRM", "ECHRNG", "EL2NSYNC", "EL3HLT", "EL3RST", "ELNRNG",
		"EUNATCH", "ENOCSI", "EL2HLT", "EBADE", "EBADR", "EXFULL", "ENOANO",
		"EBADRQC", "EBADSLT", "EDEADLOCK", "EBFONT", "ENOSTR", "ENODATA",
		"ETIME", "ENOSR", "ENONET", "ENOPKG", "EREMOTE", "ENOLINK", "EADV",
		"ESRMNT", "ECOMM", "EPROTO", "EMULTIHOP", "EDOTDOT", "EBADMSG",
		"EOVERFLOW", "ENOTUNIQ", "EBADFD", "EREMCHG", "ELIBACC", "ELIBBAD",
		"ELIBSCN", "ELIBMAX", "ELIBEXEC", "EILSEQ", "ERESTART", "ESTRPIPE",
		"EUSERS", "ENOTSOCK", "EDESTADDRREQ", "EMSGSIZE", "EPROTOTYPE",
		"ENOPROTOOPT", "EPROTONOSUPPORT", "ESOCKTNOSUPPORT", "EOPNOTSUPP",
		"EPFNOSUPPORT", "EAFNOSUPPORT", "EADDRINUSE", "EADDRNOTAVAIL",
		"ENETDOWN", "ENETUNREACH", "ENETRESET", "ECONNABORTED", "ECONNRESET",
		"ENOBUFS", "EISCONN", "ENOTCONN", "ESHUTDOWN", "ETOOMANYREFS",
		"ETIMEDOUT", "ECONNREFUSED", "EHOSTDOWN", "EHOSTUNREACH", "EALREADY",
		"EINPROGRESS", "ESTALE", "EUCLEAN", "ENOTNAM", "ENAVAIL", "EISNAM",
		"EREMOTEIO", "EDQUOT", "ENOMEDIUM", "EMEDIUMTYPE", "ECANCELED",
		"ENOKEY", "EKEYEXPIRED", "EKEYREVOKED", "EKEYREJECTED", "EOWNERDEAD",
		"ENOTRECOVERABLE", "ERFKILL", "EHWPOISION"}[error]);
}
