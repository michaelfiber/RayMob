package com.bigfoot.raymob;

import android.app.NativeActivity;
import android.os.Bundle;

import android.view.View;

//import com.google.android.gms.ads.AdError;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.FullScreenContentCallback;
import com.google.android.gms.ads.interstitial.InterstitialAd;
import com.google.android.gms.ads.interstitial.InterstitialAdLoadCallback;
import com.google.android.gms.ads.LoadAdError;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.initialization.InitializationStatus;
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener;

public class NativeLoader extends NativeActivity {

    private static NativeLoader instance;
    private InterstitialAd mInterstitialAd;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        instance = this; // Used to obtain the instance from C to call non-static methods

        // Activate immersive mode
        getWindow().getDecorView().setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_FULLSCREEN |
                        View.SYSTEM_UI_FLAG_HIDE_NAVIGATION |
                        View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY |
                        View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN |
                        View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION |
                        View.SYSTEM_UI_FLAG_LAYOUT_STABLE
        );

        // Initialize AdMob
        MobileAds.initialize(this, new OnInitializationCompleteListener() {
            @Override
            public void onInitializationComplete(InitializationStatus initializationStatus) {
                // Once the initialization is complete, you can request an advertisement here
                requestInterstitialAd();
            }
        });

        System.loadLibrary("raymob");
    }

    // Static method get the instance (from C for example)
    public static NativeLoader getInstance() {
        return instance;
    }

    // Management of immersive mode when returning to the app

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);

        // If the app has focus, re-enable immersive mode
        if (hasFocus) {
            getWindow().getDecorView().setSystemUiVisibility(
                    View.SYSTEM_UI_FLAG_FULLSCREEN |
                            View.SYSTEM_UI_FLAG_HIDE_NAVIGATION |
                            View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY |
                            View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN |
                            View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION |
                            View.SYSTEM_UI_FLAG_LAYOUT_STABLE
            );
        }
    }

    /* ADMOB */

    public void requestInterstitialAd() {
        AdRequest adRequest = new AdRequest.Builder().build();

        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                // NOTE: Change the AdMob ad id, the default one is that of Google for Test Ad interstitial
                InterstitialAd.load(NativeLoader.this, "ca-app-pub-3940256099942544/1033173712", adRequest,
                        new InterstitialAdLoadCallback() {
                            @Override
                            public void onAdLoaded(InterstitialAd interstitialAd) {
                                // Ad is loaded successfully
                                mInterstitialAd = interstitialAd;
                            }

                            @Override
                            public void onAdFailedToLoad(LoadAdError loadAdError) {
                                // Error loading ad
                                mInterstitialAd = null;
                            }
                        });
            }
        });
    }

    public boolean isInterstitialAdLoaded() {
        return mInterstitialAd != null;
    }

    public void showInterstitialAd() {
        if (mInterstitialAd != null) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    mInterstitialAd.show(NativeLoader.this);
                }
            });
        }
    }

}