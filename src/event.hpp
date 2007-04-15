/*
** Copyright (C) 2004 Jesse Chappell <jesse@essej.net>
**              and Benno Senoner and Christian Schoenebeck
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**  
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**  
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**  
*/

#ifndef __sooperlooper_event__
#define __sooperlooper_event__

#include <stdint.h>


namespace SooperLooper {

	// just symbol prototyping
	class Event;
	
	/**
	 * Generates Event objects and is responsible for resolving the position
	 * in the current audio fragment each Event actually belongs to.
	 */
	class EventGenerator {
        public:
		EventGenerator(uint32_t sampleRate);
		void updateFragmentTime(uint32_t samplesToProcess);
		Event createEvent(long fragTime=-1);
		
	protected:
		typedef double time_stamp_t; 

		inline uint32_t toFragmentPos(time_stamp_t timeStamp) {
			return uint32_t ((timeStamp - fragmentTime.begin) * fragmentTime.sample_ratio);
		}

		friend class Event;
        private:
		uint32_t uiSampleRate;
		uint32_t uiSamplesProcessed;

		struct __FragmentTime__ {
			time_stamp_t begin;        ///< Real time stamp of the beginning of this audio fragment cycle.
			time_stamp_t end;          ///< Real time stamp of the end of this audio fragment cycle.
			double        sample_ratio; ///< (Samples per cycle) / (Real time duration of cycle)
		} fragmentTime;
		
		time_stamp_t createTimeStamp();
		
    };

    /**
     * Events are usually caused by an OSC source
     * An event can only be created by an
     * EventGenerator.
     *
     * @see EventGenerator
     */
    class Event {
        public:
	    
            Event(){}

            enum type_t {
		    type_cmd_down,
		    type_cmd_up,
		    type_cmd_upforce,
		    type_cmd_hit,
		    type_control_change,
		    type_control_request,
		    type_global_control_change,
		    type_sync
            } Type;

	    enum command_t
	    {
		    UNKNOWN = -1,
		    UNDO = 0,
		    REDO,
		    REPLACE,
		    REVERSE,
		    SCRATCH,
		    RECORD,
		    OVERDUB,
		    MULTIPLY,
		    INSERT,
		    MUTE,
		    // extra features
		    DELAY,
		    REDO_TOG,
		    QUANT_TOG,
		    ROUND_TOG,
		    ONESHOT,
		    TRIGGER,
		    SUBSTITUTE,
		    UNDO_ALL,
		    REDO_ALL,
		    LAST_COMMAND
	    } Command;


	    enum control_t {
		    Unknown = -1,
		    TriggerThreshold = 0,
		    DryLevel,
		    WetLevel,
		    Feedback,
		    Rate,
		    ScratchPosition,
		    MultiUnused,
		    TapDelayTrigger,
		    UseFeedbackPlay,
		    Quantize,
		    Round,
		    RedoTap,
		    SyncMode,
		    UseRate,
		    FadeSamples,
		    TempoInput,
		    PlaybackSync,
		    EighthPerCycleLoop,
		    UseSafetyFeedback,
		    InputLatency,
		    OutputLatency,
		    TriggerLatency,
		    // read only
		    State,
		    LoopLength,
		    LoopPosition,
		    CycleLength,
		    FreeTime,
		    TotalTime,
		    Waiting,
		    TrueRate,
		    NextState,
		    // this is end of loop enum.. the following are global
		    Tempo,
		    SyncTo,
		    EighthPerCycle,
		    TapTempo,
		    MidiStart,
		    MidiStop,
		    MidiTick,
		    AutoDisableLatency,
		    SelectNextLoop,
		    SelectPrevLoop,
		    SelectAllLoops,
		    SelectedLoopNum,
		    // these are per-loop, but not used in the old plugin part
		    SaveLoop,
		    UseCommonIns,
		    UseCommonOuts,
		    HasDiscreteIO,
		    ChannelCount,
		    InPeakMeter,
		    OutPeakMeter,
		    RelativeSync,
		    InputGain,
		    AutosetLatency,
		    // this is ugly, because i want them midi bindable
		    PanChannel1,
		    PanChannel2,
		    PanChannel3,
		    PanChannel4
	    } Control;
	    
	    int8_t  Instance;
	    
	    float Value;

            inline int FragmentPos() {
                if (iFragmentPos >= 0) return (int) iFragmentPos;
                return (int) (iFragmentPos = pEventGenerator->toFragmentPos(TimeStamp));
            }

	    int source;

    protected:
            typedef EventGenerator::time_stamp_t time_stamp_t;
            Event(EventGenerator* pGenerator, EventGenerator::time_stamp_t Time);
	    Event(EventGenerator* pGenerator, int fragmentpos);
            friend class EventGenerator;
        private:
            EventGenerator* pEventGenerator; ///< Creator of the event.
            time_stamp_t    TimeStamp;       ///< Time stamp of the event's occurence.
            int             iFragmentPos;    ///< Position in the current fragment this event refers to.
	    
    };

} // namespace SooperLooper

#endif 
