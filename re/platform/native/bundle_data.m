#import <Foundation/Foundation.h>
#include "bundle_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static BOOL copy_missing(NSFileManager *fm, NSString *source, NSString *dest, NSError **error) {
    BOOL source_dir = NO, dest_dir = NO;
    if (![fm fileExistsAtPath:source isDirectory:&source_dir]) return YES;
    BOOL exists = [fm fileExistsAtPath:dest isDirectory:&dest_dir];
    if (exists && !source_dir) return YES;  // preserve settings, saves and edited scripts
    if (source_dir) {
        if (exists && !dest_dir) return NO;
        if (![fm createDirectoryAtPath:dest withIntermediateDirectories:YES
                            attributes:@{NSFilePosixPermissions: @0700} error:error]) return NO;
        NSArray *names = [fm contentsOfDirectoryAtPath:source error:error];
        if (!names) return NO;
        for (NSString *name in names) {
            if ([name hasPrefix:@"."]) continue;
            if (!copy_missing(fm, [source stringByAppendingPathComponent:name],
                              [dest stringByAppendingPathComponent:name], error)) return NO;
        }
        return YES;
    }
    if (![fm copyItemAtPath:source toPath:dest error:error]) return NO;
    return [fm setAttributes:@{NSFilePosixPermissions: @0600} ofItemAtPath:dest error:error];
}

static BOOL asset_link(NSFileManager *fm, NSString *source, NSString *dest, NSError **error) {
    NSDictionary *attrs = [fm attributesOfItemAtPath:dest error:NULL];
    if (attrs && ![attrs[NSFileType] isEqualToString:NSFileTypeSymbolicLink]) return YES;
    if ([[fm destinationOfSymbolicLinkAtPath:dest error:NULL] isEqualToString:source]) return YES;
    NSString *temp = [dest stringByAppendingFormat:@".link-%d", getpid()];
    if (![fm createSymbolicLinkAtPath:temp withDestinationPath:source error:error]) return NO;
    if (rename(temp.fileSystemRepresentation, dest.fileSystemRepresentation) != 0) {
        [fm removeItemAtPath:temp error:NULL];
        return NO;
    }
    return YES;
}

int re_bundle_prepare_data(const char *seed, char *out, size_t size) {
    @autoreleasepool {
        NSFileManager *fm = [NSFileManager defaultManager];
        NSString *source = [[NSString stringWithUTF8String:seed] stringByResolvingSymlinksInPath];
        if (![fm fileExistsAtPath:[source stringByAppendingPathComponent:@".driver-package"]]) return 0;
        const char *override = getenv("RE_USER_DATA_DIR");
        NSString *profile = override && *override ? [NSString stringWithUTF8String:override] :
            [NSHomeDirectory() stringByAppendingPathComponent:@"Library/Application Support/Driver"];
        profile = [[profile stringByStandardizingPath] stringByResolvingSymlinksInPath];
        NSString *data = [profile stringByAppendingPathComponent:@"GameData"];
        NSError *error = nil;
        BOOL ok = [fm createDirectoryAtPath:data withIntermediateDirectories:YES
                                attributes:@{NSFilePosixPermissions: @0700} error:&error];
        NSArray *names = ok ? [fm contentsOfDirectoryAtPath:source error:&error] : nil;
        if (!names) ok = NO;
        NSSet *mutable = [NSSet setWithArray:@[@"scripts", @"replaydata", @"saves", @"config.dat"]];
        for (NSString *name in names) {
            if (!ok) break;
            if ([name hasPrefix:@"."]) continue;
            NSString *src = [source stringByAppendingPathComponent:name];
            NSString *dst = [data stringByAppendingPathComponent:name];
            ok = [mutable containsObject:name.lowercaseString] ? copy_missing(fm, src, dst, &error) :
                                                               asset_link(fm, src, dst, &error);
        }
        NSString *resources = [source stringByDeletingLastPathComponent];
        NSString *textures = [resources stringByAppendingPathComponent:@"TexturePack"];
        if (ok && [fm fileExistsAtPath:textures])
            ok = asset_link(fm, textures, [data stringByAppendingPathComponent:@"TexturePack"], &error);
        if (ok) ok = [fm createDirectoryAtPath:[data stringByAppendingPathComponent:@"SAVES"]
                  withIntermediateDirectories:YES attributes:@{NSFilePosixPermissions: @0700} error:&error];
        if (ok) ok = copy_missing(fm, [resources stringByAppendingPathComponent:@"Defaults/driver.cfg"],
                                  [profile stringByAppendingPathComponent:@"driver.cfg"], &error);
        if (!ok || snprintf(out, size, "%s", data.fileSystemRepresentation) >= (int)size) {
            fprintf(stderr, "[bundle] Cannot prepare writable game data at %s: %s\n",
                    data.fileSystemRepresentation, error ? error.localizedDescription.UTF8String : "filesystem error");
            return -1;
        }
        fprintf(stderr, "[bundle] writable data: %s\n", out);
        return 1;
    }
}
