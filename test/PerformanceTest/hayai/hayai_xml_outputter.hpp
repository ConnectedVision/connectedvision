#ifndef __HAYAI_XMLOUTPUTTER
#define __HAYAI_XMLOUTPUTTER

#define TAB(x) file << "\t" << x;

#include "hayai_outputter.hpp"
#include "hayai_console.hpp"
#include <iostream>
#include <fstream>

namespace hayai
{
    /// Console outputter.

    /// Prints the result to standard output.
    class XMLOutputter
        :   public Outputter
    {
	public:
		std::ofstream file;
		XMLOutputter()
		{
			file.open ("output.xml");
		}

		~XMLOutputter()
		{
			file.close();
		}

    public:
        virtual void Begin(const std::size_t& enabledCount,
                           const std::size_t& disabledCount)
        {
            file << std::fixed;
            file << "<HAYAI>";
            file << std::endl;
        }


        virtual void End(const std::size_t& executedCount,
                         const std::size_t& disabledCount)
        {
            file << "</HAYAI>";
            file << std::endl;
        }


        inline void BeginOrSkipTest(const std::string& fixtureName,
                                    const std::string& testName,
                                    const std::string& parameters,
                                    const std::size_t& runsCount,
                                    const std::size_t& iterationsCount,
                                    const bool skip)
        {
            TAB("<" << fixtureName << "." << testName);
			
			file << " skip=\"";
			if (skip)
                file << "DISABLED\"";
            else
                file << "RUN\"";

            file << " parameters=\"" << parameters << "\""
                      << " (" << runsCount
                      << (runsCount == 1 ? " run, " : " runs, ")
                      << iterationsCount
                      << (iterationsCount == 1 ?
                          " iteration per run)" :
                          " iterations per run)")
					  << ">";			
			file << std::endl;
        }


        virtual void BeginTest(const std::string& fixtureName,
                               const std::string& testName,
                               const std::string& parameters,
                               const std::size_t& runsCount,
                               const std::size_t& iterationsCount)
        {
            BeginOrSkipTest(fixtureName,
                            testName,
                            parameters,
                            runsCount,
                            iterationsCount,
                            false);
        }


        virtual void SkipDisabledTest(const std::string& fixtureName,
                                      const std::string& testName,
                                      const std::string& parameters,
                                      const std::size_t& runsCount,
                                      const std::size_t& iterationsCount)
        {
            BeginOrSkipTest(fixtureName,
                            testName,
                            parameters,
                            runsCount,
                            iterationsCount,
                            true);
        }


        virtual void EndTest(const std::string& fixtureName,
                             const std::string& testName,
                             const std::string& parameters,
                             const TestResult& result)
        {
			TAB("</" << fixtureName << "." << testName << ">");
			file << std::endl;
			

/*#define PAD(x) std::coute << std::setw(34) << x << std::endl;
#define PAD_DEVIATION(description,                                      \
                      deviated,                                         \
                      average,                                          \
                      unit)                                             \
            {                                                           \
                double _d_ =                                            \
                    double(deviated) - double(average);                 \
                                                                        \
                PAD(description <<                                      \
                    deviated << " " << unit << " (" <<                  \
                    (deviated < average ?                               \
                     Console::TextRed :                                 \
                     Console::TextGreen) <<                             \
                    (deviated > average ? "+" : "") <<                  \
                    _d_ << " " << unit << " / " <<                      \
                    (deviated > average ? "+" : "") <<                  \
                    (_d_ * 100.0 / average) << " %" <<                  \
                    Console::TextDefault << ")");                       \
            }
#define PAD_DEVIATION_INVERSE(description,                              \
                              deviated,                                 \
                              average,                                  \
                              unit)                                     \
            {                                                           \
                double _d_ =                                            \
                    double(deviated) - double(average);                 \
                                                                        \
                PAD(description <<                                      \
                    deviated << " " << unit << " (" <<                  \
                    (deviated > average ?                               \
                     Console::TextRed :                                 \
                     Console::TextGreen) <<                             \
                    (deviated > average ? "+" : "") <<                  \
                    _d_ << " " << unit << " / " <<                      \
                    (deviated > average ? "+" : "") <<                  \
                    (_d_ * 100.0 / average) << " %" <<                  \
                    Console::TextDefault << ")");                       \
            }
			std::coute << Console::TextGreen << "[     DONE ]"
                      << Console::TextYellow << " "
                      << fixtureName << "."
                      << testName
                      << parameters
                      << Console::TextDefault << " ("
                      << std::setprecision(6)
                      << (result.TimeTotal() / 1000000.0) << " ms)"
                      << std::endl;

            std::coute << Console::TextBlue << "[   RUNS   ] "
                      << Console::TextDefault
                      << "       Average time: "
                      << std::setprecision(3)
                      << result.RunTimeAverage() / 1000.0 << " us"
                      << std::endl;

            PAD_DEVIATION_INVERSE("Fastest: ",
                                  (result.RunTimeMinimum() / 1000.0),
                                  (result.RunTimeAverage() / 1000.0),
                                  "us");
            PAD_DEVIATION_INVERSE("Slowest: ",
                                  (result.RunTimeMaximum() / 1000.0),
                                  (result.RunTimeAverage() / 1000.0),
                                  "us");

            std::coute << std::setprecision(5);

            PAD("");
            PAD("Average performance: " <<
                result.RunsPerSecondAverage() << " runs/s");
            PAD_DEVIATION("Best performance: ",
                          result.RunsPerSecondMaximum(),
                          result.RunsPerSecondAverage(),
                          "runs/s");
            PAD_DEVIATION("Worst performance: ",
                          result.RunsPerSecondMinimum(),
                          result.RunsPerSecondAverage(),
                          "runs/s");

            std::coute << Console::TextBlue << "[ITERATIONS] "
                      << Console::TextDefault
                      << std::setprecision(3)
                      << "       Average time: "
                      << result.IterationTimeAverage() / 1000.0 << " us"
                      << std::endl;

            PAD_DEVIATION_INVERSE("Fastest: ",
                                  (result.IterationTimeMinimum() / 1000.0),
                                  (result.IterationTimeAverage() / 1000.0),
                                  "us");
            PAD_DEVIATION_INVERSE("Slowest: ",
                                  (result.IterationTimeMaximum() / 1000.0),
                                  (result.IterationTimeAverage() / 1000.0),
                                  "us");

            std::coute << std::setprecision(5);

            PAD("");
            PAD("Average performance: " <<
                result.IterationsPerSecondAverage() <<
                " iterations/s");
            PAD_DEVIATION("Best performance: ",
                          (result.IterationsPerSecondMaximum()),
                          (result.IterationsPerSecondAverage()),
                          "iterations/s");
            PAD_DEVIATION("Worst performance: ",
                          (result.IterationsPerSecondMinimum()),
                          (result.IterationsPerSecondAverage()),
                          "iterations/s");
#undef PAD_DEVIATION_INVERSE
#undef PAD_DEVIATION
#undef PAD*/
        }
    };
}
#endif
