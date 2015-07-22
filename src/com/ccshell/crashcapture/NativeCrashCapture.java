//Copyright 2014 miechalzhao@gmail Authors. All rights reserved.
//Use of this source code is governed by a BSD-style license that can be
//found in the LICENSE file.
package com.ccshell.crashcapture;

/*
 * @brief Provides system native crash capture.
 * if native crash occured that can be catch by NativeCrashCapture service.
 * NativeCrashCapture generate native crash dump to the directory which the app specified.
 */
public class NativeCrashCapture {
	private static boolean sInitNativeCrashCapture = false;

	static {
		try {
			System.loadLibrary("crashcapture");
			sInitNativeCrashCapture = true;
		} catch (Exception e) {
			sInitNativeCrashCapture = false;
			e.printStackTrace();
		}
	}

	/**
	 * @brief init crash capture
	 * @param crashDirectory provider directory for native generate crash dump.
	 * @param appVersion application version code.
	 * @return 0 init succeeded, -1 crashcapture library unload.
	 */
	public static int init(String crashDirectory, String appVersion) {
		if (sInitNativeCrashCapture) {
			sInitNativeCrashCapture = false;
			return nativeInit(crashDirectory, "v" + appVersion + "-");
		}

		return -1;
	}

	private static native int nativeInit(String crashPath, String version);
}
