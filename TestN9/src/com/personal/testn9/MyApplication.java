package com.personal.testn9;

import java.util.UUID;

import android.app.Application;
import android.content.Context;
import android.content.SharedPreferences;

public class MyApplication extends Application {
    private static MyApplication app;
    public static MyApplication getInstance(){
        return app;
    }
    
    public void onCreate() {
        super.onCreate();
        app = this;
    }
    public String getUUID(){
        String uuid = "00000";
        String key = "MTP_UUID";
        SharedPreferences sharedPref = getSharedPreferences("MTP",Context.MODE_PRIVATE);
        if (!sharedPref.contains(key)){
            uuid = UUID.randomUUID().toString();
            SharedPreferences.Editor editor = sharedPref.edit();
            editor.putString(key, uuid);
            editor.commit();
        }
        else{
            uuid = sharedPref.getString(key, "000000");
        }
        return uuid;
    }

}
