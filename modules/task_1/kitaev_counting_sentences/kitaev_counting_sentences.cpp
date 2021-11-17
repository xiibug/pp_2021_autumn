// Copyright 2021 Kitaev Pavel

#include <mpi.h>
#include "../../../modules/task_1/kitaev_counting_sentences/kitaev_counting_sentences.h"

int sequentialCountingSentences(std::string text) {
  const int Len = text.length();  // Getting the length of the text
  int Count = 0;  // Total number of counted offers

  for (int i = 0; i < Len; i++) {
    if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?')) {
      if (text[i + 1] == '\0' || text[i + 1] == ' ') {
        Count++;
      }
    }
  }
  return Count;
}

int parallelCountingSentences(std::string text) {
  int ProcRank;  // Process number
  int ProcNum;  // Process quantity

  MPI_Comm_size(MPI_COMM_WORLD,
                &ProcNum);  // Get the number of processes
  MPI_Comm_rank(MPI_COMM_WORLD,
                &ProcRank);  // Get the number of the current process

  const int Len = text.length();  // Getting the length of the text
  int Count = 0;  // Total number of counted offers
  int TempCount = 0;  // Number of offers counted by each process

  int Separation = 0;  // Number of characters to count for each process
  int Remaining = 0;  // Remaining characters

  if (ProcRank == 0) {
    if (ProcNum > Len) {
      throw(-1);
    }

    if (ProcNum == 1) {
      Separation = Len;
    } else {
      Separation = Len / (ProcNum - 1);
      Remaining = Len % (ProcNum - 1);
    }

    // Sending data to all processes except the main one
    for (int i = 1; i < ProcNum; i++) {
      MPI_Send(&Separation, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
  }

  // We accept data by all processes except the main one
  if (ProcRank != 0) {
    MPI_Status status;
    MPI_Recv(&Separation, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    for (int i = Separation * (ProcRank - 1); i < Separation * ProcRank; i++) {
      if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?')) {
        if (text[i + 1] == '\0' || text[i + 1] == ' ') {
          TempCount++;
        }
      }
    }
  } else {
    int t = 0;
    if (ProcNum != 1) {
      t = Len - Remaining;
    }
    for (int i = t; i < Len; i++) {
      if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?')) {
        if (i == Len - 1) {
          TempCount++;
        } else if (text[i] == '\0' || text[i + 1] == ' ') {
          TempCount++;
        }
      }
    }
  }

  MPI_Reduce(&TempCount, &Count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  return Count;
}

std::string getText() {
  std::string text = "Nikola Tesla, (born July 9/10, 1856, Smiljan, Austrian "
  "Empire [now in Croatia]-died January 7, 1943, New York), Serbian American "
  "inventor and engineer who discovered and patented the rotating magnetic "
  "field, the basis of most alternating-current machinery. He also developed "
  "the three-phase system of electric power transmission. He immigrated to the "
  "United States in 1884 and sold the patent rights to his system of "
  "alternating-current dynamos, transformers, and motors to George "
  "Westinghouse. In 1891 he invented the Tesla coil, an induction coil widely "
  "used in radio technology. Tesla was from a family of Serbian origin. His "
  "father was an Orthodox priest, his mother was unschooled but highly "
  "intelligent. As he matured, he displayed remarkable imagination and "
  "creativity as well as a poetic touch. Training for an engineering career, "
  "he attended the Technical University at Graz, Austria, and the University "
  "of Prague. At Graz he first saw the Gramme dynamo, which operated as a "
  "generator and, when reversed, became an electric motor, and he conceived a "
  "way to use alternating current to advantage. Later, at Budapest, he "
  "visualized the principle of the rotating magnetic field and developed plans"
  "for an induction motor that would become his first step toward the "
  "successful utilization of alternating current. In 1882 Tesla went to work "
  "in Paris for the Continental Edison Company, and, while on assignment to "
  "Strassburg in 1883, he constructed, after work hours, his first induction "
  "motor. Tesla sailed for America in 1884, arriving in New York with four "
  "cents in his pocket, a few of his own poems, and calculations for a flying "
  "machine. He first found employment with Thomas Edison, but the two "
  "inventors were far apart in background and methods, and their separation "
  "was inevitable. In May 1888 George Westinghouse, head of the Westinghouse "
  "Electric Company in Pittsburgh, bought the patent rights to Teslas "
  "polyphase system of alternating-current dynamos, transformers, and motors. "
  "The transaction precipitated a titanic power struggle between Edisons "
  "direct-current systems and the Tesla-Westinghouse alternating-current "
  "approach, which eventually won out. Tesla soon established his own "
  "laboratory, where his inventive mind could be given free rein. He "
  "experimented with shadowgraphs similar to those that later were to be used "
  "by Wilhelm Rontgen when he discovered X-rays in 1895. Teslas countless "
  "experiments included work on a carbon button lamp, on the power of "
  "electrical resonance, and on various types of lighting. In order to allay "
  "fears of alternating currents, Tesla gave exhibitions in his laboratory in "
  "which he lit lamps by allowing electricity to flow through his body. He was "
  "often invited to lecture at home and abroad. The Tesla coil, which he "
  "invented in 1891, is widely used today in radio and television sets and "
  "other electronic equipment. That year also marked the date of Teslas "
  "citizenship. Westinghouse used Teslas alternating current system to light "
  "the Worlds Columbian Exposition at Chicago in 1893. This success was a "
  "factor in their winning the contract to install the first power machinery "
  "at Niagara Falls, which bore Teslas name and patent numbers. The project "
  "carried power to Buffalo by 1896. In 1898 Tesla announced his invention of "
  "a teleautomatic boat guided by remote control. When skepticism was voiced, "
  "Tesla proved his claims for it before a crowd in Madison Square Garden. In "
  "Colorado Springs, Colorado, where he stayed from May 1899 until early 1900, "
  "Tesla made what he regarded as his most important-discovery terrestrial "
  "stationary waves. By this discovery he proved that Earth could be used as a "
  "conductor and made to resonate at a certain electrical frequency. He also "
  "lit 200 lamps without wires from a distance of 40 km (25 miles) and created "
  "man-made lightning, producing flashes measuring 41 metres (135 feet). At "
  "one time he was certain he had received signals from another planet in his "
  "Colorado laboratory, a claim that was met with derision in some scientific "
  "journals. Returning to New York in 1900, Tesla began construction on Long "
  "Island of a wireless world broadcasting tower, with $150,000 capital from "
  "the American financier J.Pierpont Morgan. Tesla claimed he secured the loan "
  "by assigning 51 percent of his patent rights of telephony and telegraphy to "
  "Morgan. He expected to provide worldwide communication and to furnish "
  "facilities for sending pictures, messages, weather warnings, and stock "
  "reports. The project was abandoned because of a financial panic, labour "
  "troubles, and Morgans withdrawal of support. It was Teslas greatest "
  "defeat. Teslas work then shifted to turbines and other projects. Because "
  "of a lack of funds, his ideas remained in his notebooks, which are still "
  "examined by enthusiasts for unexploited clues. In 1915 he was severely "
  "disappointed when a report that he and Edison were to share the Nobel Prize "
  "proved erroneous. Tesla was the recipient of the Edison Medal in 1917, "
  "the highest honour that the American Institute of Electrical Engineers "
  "could bestow. Tesla allowed himself only a few close friends. Among them "
  "were the writers Robert Underwood Johnson, Mark Twain, and Francis Marion "
  "Crawford. He was quite impractical in financial matters and an eccentric, "
  "driven by compulsions and a progressive germ phobia. But he had a way of "
  "intuitively sensing hidden scientific secrets and employing his inventive "
  "talent to prove his hypotheses. Tesla was a godsend to reporters who sought "
  "sensational copy but a problem to editors who were uncertain how seriously "
  "his futuristic prophecies should be regarded. Caustic criticism greeted his "
  "speculations concerning communication with other planets, his assertions "
  "that he could split the Earth like an apple, and his claim of having "
  "invented a death ray capable of destroying 10,000 airplanes at a distance "
  "of 400 km (250 miles). After Teslas death the custodian of alien property "
  "impounded his trunks, which held his papers, his diplomas and other "
  "honours,  his letters, and his laboratory notes. These were eventually "
  "inherited by Teslas nephew, Sava Kosanovich, and later housed in the "
  "Nikola Tesla Museum in Belgrade. Hundreds filed into New York Citys "
  "Cathedral of St.John the Divine for his funeral services, and a flood of "
  "messages acknowledged the loss of a great genius. Three Nobel Prize "
  "recipients addressed their tribute to 'one of the outstanding intellects "
  "of the world who paved the way for many of the technological developments "
  "of modern times'.";

  return text;
}
