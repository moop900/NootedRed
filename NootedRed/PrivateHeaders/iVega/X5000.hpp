// Copyright © 2022-2025 ChefKiss. Licensed under the Thou Shalt Not Profit License version 1.5.
// See LICENSE for details.

#pragma once
#include <Headers/kern_patcher.hpp>
#include <PrivateHeaders/GPUDriversAMD/Accel/HWEngine.hpp>
#include <PrivateHeaders/GPUDriversAMD/AddrLib.hpp>
#include <PrivateHeaders/ObjectField.hpp>

namespace iVega {
    class X5000 {
        using t_GenericConstructor = void (*)(void *that);

        friend class X6000;

        bool initialised {false};
        ObjectField<void *> pm4EngineField {"PM4 Engine"};
        ObjectField<void *> sdma0EngineField {"SDMA0 Engine"};
        ObjectField<UInt32> displayPipeCountField {"Display Pipe Count"};
        ObjectField<UInt32> seCountField {"Shader Engine Count"};
        ObjectField<UInt32> shPerSEField {"Shader Array per Shader Engine"};
        ObjectField<UInt32> cuPerSHField {"Compute Units per Shader Array"};
        ObjectField<bool> hasUVD0Field {"Has UVD0"};
        ObjectField<bool> hasVCEField {"Has VCE"};
        ObjectField<bool> hasVCN0Field {"Has VCN0"};
        ObjectField<bool> hasSDMAPagingQueueField {"Has SDMA Paging Queue"};
        ObjectField<UInt32> familyTypeField {"Family Type"};
        ObjectField<Gfx9ChipSettings> chipSettingsField {"AddrLib Chip Settings"};
        t_GenericConstructor orgGFX9PM4EngineConstructor {nullptr};
        t_GenericConstructor orgGFX9SDMAEngineConstructor {nullptr};
        mach_vm_address_t orgSetupAndInitializeHWCapabilities {0};
        mach_vm_address_t orgGFX9SetupAndInitializeHWCapabilities {0};
        mach_vm_address_t orgGetHWChannel {0};
        mach_vm_address_t orgAdjustVRAMAddress {0};
        mach_vm_address_t orgAllocateAMDHWAlignManager {0};
        mach_vm_address_t orgObtainAccelChannelGroup {0};
        mach_vm_address_t orgHwlConvertChipFamily {0};

        public:
        static X5000 &singleton();

        void init();

        private:
        void processKext(KernelPatcher &patcher, size_t id, mach_vm_address_t slide, size_t size);
        static bool wrapAllocateHWEngines(void *that);
        static void wrapSetupAndInitializeHWCapabilities(void *that);
        static void wrapGFX9SetupAndInitializeHWCapabilities(void *that);
        static void *wrapGetHWChannel(void *that, AMDHWEngineType engineType, UInt32 ringId);
        static void wrapInitializeFamilyType(void *that);
        static void *wrapAllocateAMDHWDisplay(void *that);
        static UInt64 wrapAdjustVRAMAddress(void *that, UInt64 addr);
        static void *wrapAllocateAMDHWAlignManager(void *that);
        static UInt32 wrapGetDeviceType();
        static UInt32 wrapReturnZero();
        static void *wrapObtainAccelChannelGroup(void *that, UInt32 priority);
        static void *wrapObtainAccelChannelGroup1304(void *that, UInt32 priority, void *task);
        static UInt32 wrapHwlConvertChipFamily(void *that, UInt32 family, UInt32 revision);
    };
};    // namespace iVega
