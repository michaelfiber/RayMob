#ifndef ADMOB_H
#define ADMOB_H

#include <stdbool.h>

void ReleaseNativeLoader(void);

void RequestInterstitialAd(void);
bool IsInterstitialAdLoaded(void);
void ShowInterstitialAd(void);

#endif
