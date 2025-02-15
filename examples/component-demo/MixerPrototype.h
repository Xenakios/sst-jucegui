//
// Created by Paul Walker on 5/25/22.
//

#ifndef SST_JUCEGUI_MIXERPROTO_H
#define SST_JUCEGUI_MIXERPROTO_H

#include <sst/jucegui/style/Layouts.h>

#include <sst/jucegui/components/VSlider.h>
#include <sst/jucegui/components/Knob.h>
#include <sst/jucegui/components/Label.h>
#include <sst/jucegui/components/ToggleButton.h>
#include <sst/jucegui/components/NamedPanel.h>
#include <sst/jucegui/components/WindowPanel.h>
#include "ExampleUtils.h"

namespace cmp = sst::jucegui::components;

struct MixerProto : public sst::jucegui::components::WindowPanel
{
    static constexpr const char *name = "Mixer Prototype";

    struct Channel : juce::Component
    {
        Channel(const std::string &label)
        {
            level = std::make_unique<cmp::VSlider>();
            level->setSource(&levCM);
            levCM.setValueFromGUI((rand() % 100) / 100.0 * 0.5 + 0.5);
            addAndMakeVisible(*level);

            pan = std::make_unique<cmp::Knob>();
            panCM.min = -1;
            panCM.setValueFromGUI((rand() % 100) / 100.0 * 0.4 - 0.2);
            pan->setSource(&panCM);
            addAndMakeVisible(*pan);

            mute = std::make_unique<cmp::ToggleButton>();
            mute->setSource(&muteBM);
            mute->setLabel("M");
            addAndMakeVisible(*mute);
            solo = std::make_unique<cmp::ToggleButton>();
            solo->setSource(&soloBM);
            solo->setLabel("S");
            addAndMakeVisible(*solo);

            lab = std::make_unique<cmp::Label>();
            lab->setText(label);
            addAndMakeVisible(*lab);
        }

        ~Channel()
        {
            solo->setSource(nullptr);
            pan->setSource(nullptr);
            mute->setSource(nullptr);
            level->setSource(nullptr);
        }

        std::unique_ptr<cmp::VSlider> level;
        std::unique_ptr<cmp::Knob> pan;
        std::unique_ptr<cmp::ToggleButton> mute, solo;
        std::unique_ptr<cmp::Label> lab;

        ConcreteCM levCM, panCM;
        ConcreteBinM muteBM, soloBM;

        void resized()
        {
            auto b = getLocalBounds();
            auto w = b.getWidth();
            auto t = b.withHeight(20);
            auto k = b.withHeight(w).translated(0, 22);
            auto s = b.withTrimmedTop(20 + w + 4).withTrimmedBottom(17);
            auto l = b.withTop(s.getBottom());

            pan->setBounds(k);
            level->setBounds(s);

            solo->setBounds(t.withWidth(t.getWidth() / 2).reduced(1));
            mute->setBounds(t.withTrimmedLeft(t.getWidth() / 2).reduced(1));

            lab->setBounds(l);
        }
    };

    struct Mixer : juce::Component
    {
        Mixer()
        {
            for (int i = 0; i < 12; ++i)
            {
                auto c = std::make_unique<Channel>(std::to_string(i));
                addAndMakeVisible(*c);
                channels.push_back(std::move(c));
            }
        }
        ~Mixer() {}
        void resized() override
        {
            auto b = getLocalBounds();
            auto e = sst::jucegui::style::EvenDivision<float>(
                b.toFloat(), channels.size(), sst::jucegui::style::EvenDivision<float>::HORIZONTAL);
            auto r = e.begin();
            for (const auto &c : channels)
            {
                c->setBounds((*r).toNearestInt());
                r++;
            }
        }
        std::vector<std::unique_ptr<Channel>> channels;
    };

    MixerProto()
    {
        panelOne = std::make_unique<sst::jucegui::components::NamedPanel>("Mixer Prototype");
        panelOne->setContentAreaComponent(std::make_unique<Mixer>());

        addAndMakeVisible(*panelOne);
    }

    void resized() override { panelOne->setBounds(10, 10, 500, 300); }

    std::unique_ptr<sst::jucegui::components::NamedPanel> panelOne;
};

#endif // SST_JUCEGUI_KNOBDEMO_H
