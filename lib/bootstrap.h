#pragma once

#include <appmodel.h>
#include <windows.h>

typedef HRESULT(WINAPI *MddBootstrapInitialize)(
  UINT32 majorMinorVersion,
  PCWSTR versionTag,
  PACKAGE_VERSION minVersion
);

static int
bare__try_bootstrap_runtime(void) {
  HMODULE bootstrap = LoadLibraryW(L"Microsoft.WindowsAppRuntime.Bootstrap.dll");

  MddBootstrapInitialize initialize = reinterpret_cast<MddBootstrapInitialize>(
    GetProcAddress(bootstrap, "MddBootstrapInitialize")
  );

  if (initialize == nullptr) {
    FreeLibrary(bootstrap);

    return -1;
  }

  HRESULT res = initialize(Release::MajorMinor, Release::VersionTag, {Runtime::Version::UInt64});

  if (FAILED(res)) {
    FreeLibrary(bootstrap);

    return -1;
  }

  return 0;
}
