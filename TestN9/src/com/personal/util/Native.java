package com.personal.util;

public class Native {

    static{
        System.loadLibrary("mono");
        System.loadLibrary("TestN9");
    }
    
    public static native void testDlopen();
}
