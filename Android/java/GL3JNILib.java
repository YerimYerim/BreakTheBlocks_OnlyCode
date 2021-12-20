package com.example.Blocks;

public class GL3JNILib {
    static {
        System.loadLibrary("Blocks");
    }
    public static native void Start(int width, int height);
    public static native void Update();
    public static native void InputEvent(boolean isTouch, float x, float y);
    public static native String getRoundCount();
}
