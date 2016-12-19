#ifndef SEQ64_RTMIDI_INFO_HPP
#define SEQ64_RTMIDI_INFO_HPP

/**
 * \file          rtmidi_info.hpp
 *
 *  A base class for enumerating MIDI clients and ports.
 *
 * \author        refactoring by Chris Ahlstrom
 * \date          2016-12-08
 * \updates       2016-12-18
 * \license       See the rtexmidi.lic file.  Too big for a header file.
 * \license       GNU GPLv2 or above
 *
 *  This class is like the rtmidi_in and rtmidi_out classes, but cut down to
 *  the interface functions needed to enumerate clients and ports.  It is a
 *  wrapper/selector for the new midi_info class and its children.
 */

#include "midi_api.hpp"                     /* seq64::midi[_in][_out]_api   */
#include "midi_info.hpp"

/*
 * Do not document the namespace; it breaks Doxygen.
 */

namespace seq64
{

/**
 *  A class for enumerating MIDI clients and ports.  New, but ripe for
 *  refactoring nonetheless.
 */

class rtmidi_info
{
    friend class midibus;
    friend class rtmidi_in;
    friend class rtmidi_out;

private:

    /**
     *  Provides access to the selected API (currently only JACK or ALSA.
     */

    midi_info * m_info_api;

    /**
     *  To save from repeated queries, we save this value.  Its default value
     *  is RTMIDI_API_UNSPECIFIED.
     */

    static rtmidi_api sm_selected_api;

public:

    rtmidi_info (rtmidi_api api = RTMIDI_API_UNSPECIFIED);

    virtual ~rtmidi_info ();

    /*
     *  A static function to determine the current rtmidi version.
     */

    static std::string get_version ();

    /*
     *  A static function to determine the available compiled MIDI APIs.  The
     *  values returned in the std::vector can be compared against the
     *  enumerated list values.  Note that there can be more than one API
     *  compiled for certain operating systems.
     */

    static void get_compiled_api (std::vector<rtmidi_api> & apis);

    /**
     *  Sets the input or output mode for getting data.
     */

    virtual void midi_mode (bool flag)
    {
        get_api()->midi_mode(flag);
    }

    /**
     *  Gets the buss/client ID for a MIDI interfaces.  This is the left-hand
     *  side of a X:Y pair (such as 128:0).
     *
     *  This function is a new part of the RtMidi interface.
     *
     * \param index
     *      The ordinal index of the desired interface to look up.
     *
     * \return
     *      Returns the buss/client value as provided by the selected API.
     */

    virtual unsigned get_client_id (unsigned index)
    {
        return get_api()->get_client_id(index);
    }

    virtual std::string get_client_name (unsigned index)
    {
        return get_api()->get_client_name(index);
    }

    virtual unsigned get_port_count ()
    {
        return get_api()->get_port_count();
    }

    virtual unsigned get_port_number (unsigned index)
    {
        return get_api()->get_port_number(index);
    }

    virtual std::string get_port_name (unsigned index)
    {
        return get_api()->get_port_name(index);
    }

    virtual unsigned get_all_port_info ()
    {
        return get_api()->get_all_port_info();
    }

    /**
     *  Returns a list of all the ports as an ASCII string.
     */

    std::string port_list () const
    {
        return get_api()->port_list();
    }

    /**
     * \getter sm_selected_api
     */

    static rtmidi_api & selected_api ()
    {
        return sm_selected_api;
    }

    /**
     * \getter m_info_api const version
     */

    const midi_info * get_api () const
    {
        return m_info_api;
    }

    /**
     * \getter m_info_api non-const version
     */

    midi_info * get_api ()
    {
        return m_info_api;
    }

protected:

    /**
     * \setter sm_selected_api
     */

    static void selected_api (const rtmidi_api & api)
    {
        sm_selected_api = api;
    }

    /**
     * \setter m_info_api
     */

    void set_api (midi_info * ma)
    {
        if (not_nullptr(ma))
            m_info_api = ma;
    }

    /**
     * \setter m_info_api
     */

    void delete_api ()
    {
        if (not_nullptr(m_info_api))
        {
            delete m_info_api;
            m_info_api = nullptr;
        }
    }

protected:

    void openmidi_api (rtmidi_api api);

};          // class rtmidi_info

}           // namespace seq64

#endif      // SEQ64_RTMIDI_INFO_HPP

/*
 * rtmidi_info.hpp
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */
