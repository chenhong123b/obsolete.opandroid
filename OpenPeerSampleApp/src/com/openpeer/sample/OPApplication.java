package com.openpeer.sample;

import android.app.Application;
import android.content.Context;

import com.openpeer.sdk.app.OPHelper;
import com.urbanairship.AirshipConfigOptions;
import com.urbanairship.UAirship;
import com.urbanairship.push.PushManager;

public class OPApplication extends Application {
	private static OPApplication instance;
	private boolean mInBackground;

	static {
		try {
			System.loadLibrary("z_shared");
			System.loadLibrary("openpeer");

		} catch (UnsatisfiedLinkError use) {
			use.printStackTrace();
		}
	}

	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
		instance = this;

        AirshipConfigOptions options = AirshipConfigOptions.loadDefaultOptions(this);
        UAirship.takeOff(this, options);
        PushManager.enablePush();

		OPHelper.getInstance().init(this, null);
		OPHelper.getInstance().setChatGroupMode(OPHelper.MODE_CONTACTS_BASED);
		OPSessionManager.getInstance().init();
	}

	public static OPApplication getInstance() {
		// TODO Auto-generated method stub
		return instance;
	}

	public boolean isInBackground() {
		// TODO Auto-generated method stub
		return mInBackground;
	}

	public void onEnteringForeground() {
		this.mInBackground = false;

	}

	public void onEnteringBackground() {
		this.mInBackground = true;
	}

}
