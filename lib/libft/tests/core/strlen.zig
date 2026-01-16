const std = @import("std");
const c = @cImport({
	@cInclude("core/string.h");
});

test "strlen" {
    const s = "hello";
    try std.testing.expect(c.ft_strlen(s) == 5);
}
