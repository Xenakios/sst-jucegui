/*
 * sst-juce-guil - an open source library of juce widgets
 * built by Surge Synth Team.
 *
 * Copyright 2023, various authors, as described in the GitHub
 * transaction log.
 *
 * sst-basic-blocks is released under the MIT license, as described
 * by "LICENSE.md" in this repository. This means you may use this
 * in commercial software if you are a JUCE Licensee. If you use JUCE
 * in the open source / GPL3 context, your combined work must be
 * released under GPL3.
 *
 * All source in sst-juce-gui available at
 * https://github.com/surge-synthesizer/sst-juce-gui
 */

#ifndef INCLUDE_SST_JUCEGUI_COMPONENTS_DRAGGABLETEXTEDITABLEVALUE_H
#define INCLUDE_SST_JUCEGUI_COMPONENTS_DRAGGABLETEXTEDITABLEVALUE_H

#include <string>

#include <juce_gui_basics/juce_gui_basics.h>

#include <sst/jucegui/style/StyleAndSettingsConsumer.h>
#include <sst/jucegui/style/StyleSheet.h>
#include <sst/jucegui/components/BaseStyles.h>

#include "ComponentBase.h"

namespace sst::jucegui::components
{
struct DraggableTextEditableValue : public juce::Component,
                                    public EditableComponentBase<DraggableTextEditableValue>,
                                    public Modulatable<DraggableTextEditableValue>,
                                    public style::SettingsConsumer,
                                    public style::StyleConsumer
{
    struct Styles : TextualControlStyles
    {
        using sclass = style::StyleSheet::Class;
        using sprop = style::StyleSheet::Property;
        static constexpr sclass styleClass{"draggabletexteditor"};

        static constexpr sprop bgedcol{"background.editing.color"};
        static void initialize()
        {
            style::StyleSheet::addClass(styleClass)
                .withBaseClass(TextualControlStyles::styleClass)
                .withProperty(bgedcol);
        }
    };

    DraggableTextEditableValue();

    void paint(juce::Graphics &g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent &e) override;
    void mouseUp(const juce::MouseEvent &e) override;
    void mouseDrag(const juce::MouseEvent &e) override;
    void mouseWheelMove(const juce::MouseEvent &event,
                        const juce::MouseWheelDetails &wheel) override;

    void mouseEnter(const juce::MouseEvent &e) override { startHover(); }
    void mouseExit(const juce::MouseEvent &e) override { endHover(); }

    void mouseDoubleClick(const juce::MouseEvent &e) override;

    void setFromEditor();
    void onStyleChanged() override;

  private:
    float valueOnMouseDown{0.f};
    std::unique_ptr<juce::TextEditor> underlyingEditor;
};
} // namespace sst::jucegui::components

#endif // SST_JUCEGUI_DRAGGABLETEXTEDITABLEVALUE_H
