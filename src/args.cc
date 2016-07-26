/**
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "args.h"
#include "stdlib.h"
#include <string.h>
#include <iostream>
#include <fstream>

Args::Args() {
  lr = 0.025;
  dim = 100;
  ws = 5;
  epoch = 5;
  minCount = 5;
  neg = 5;
  wordNgrams = 1;
  sampling = sampling_name::sqrt;
  loss = loss_name::ns;
  model = model_name::sg;
  bucket = 2000000;
  minn = 3;
  maxn = 6;
  onlyWord = 0;
  thread = 12;
  verbose = 1000;
  t = 1e-4;
  label = L"__label__";
}

void Args::parseArgs(int argc, char** argv) {
  std::string command(argv[1]);
  if (command == "supervised") {
    model = model_name::sup;
    loss = loss_name::softmax;
  } else if (command == "cbow") {
    model == model_name::cbow;
  }
  int ai = 2;
  while (ai < argc) {
    if (argv[ai][0] != '-') {
      std::wcout << "Provided argument without a dash! Usage:" << std::endl;
      printHelp();
      exit(EXIT_FAILURE);
    }
    if (strcmp(argv[ai], "-h") == 0) {
      std::wcout << "Here is the help! Usage:" << std::endl;
      printHelp();
      exit(EXIT_FAILURE);
    } else if (strcmp(argv[ai], "-input") == 0) {
      input = std::string(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-test") == 0) {
      test = std::string(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-output") == 0) {
      output = std::string(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-lr") == 0) {
      lr = atof(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-dim") == 0) {
      dim = atoi(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-ws") == 0) {
      ws = atoi(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-epoch") == 0) {
      epoch = atoi(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-minCount") == 0) {
      minCount = atoi(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-neg") == 0) {
      neg = atoi(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-wordNgrams") == 0) {
      wordNgrams = atoi(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-sampling") == 0) {
      if (strcmp(argv[ai + 1], "sqrt") == 0) {
        sampling = sampling_name::sqrt;
      } else if (strcmp(argv[ai + 1], "log") == 0) {
        sampling = sampling_name::log;
      } else if (strcmp(argv[ai + 1], "uni") == 0) {
        sampling = sampling_name::uni;
      } else {
        std::wcout << "Unknown sampling: " << argv[ai + 1] << std::endl;
        printHelp();
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[ai], "-loss") == 0) {
      if (strcmp(argv[ai + 1], "hs") == 0) {
        loss = loss_name::hs;
      } else if (strcmp(argv[ai + 1], "ns") == 0) {
        loss = loss_name::ns;
      } else if (strcmp(argv[ai + 1], "softmax") == 0) {
        loss = loss_name::softmax;
      } else {
        std::wcout << "Unknown loss: " << argv[ai + 1] << std::endl;
        printHelp();
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[ai], "-bucket") == 0) {
      bucket = atoi(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-minn") == 0) {
      minn = atoi(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-maxn") == 0) {
      maxn = atoi(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-onlyWord") == 0) {
      onlyWord = atoi(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-thread") == 0) {
      thread = atoi(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-verbose") == 0) {
      verbose = atoi(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-t") == 0) {
      t = atof(argv[ai + 1]);
    } else if (strcmp(argv[ai], "-label") == 0) {
      std::string str = std::string(argv[ai + 1]);
      label = std::wstring(str.begin(), str.end());
    } else {
      std::wcout << "Unknown argument: " << argv[ai] << std::endl;
      printHelp();
      exit(EXIT_FAILURE);
    }
    ai += 2;
  }
  if (input.empty() || output.empty()) {
    std::wcout << "Empty input or output path." << std::endl;
    printHelp();
    exit(EXIT_FAILURE);
  }
}

void Args::printHelp() {
  std::wcout
    << "\n"
    << "The following arguments are mandatory:\n"
    << "  -input      training file path\n"
    << "  -output     output file path\n\n"
    << "The following arguments are optional:\n"
    << "  -lr         learning rate [" << lr << "]\n"
    << "  -dim        size of word vectors [" << dim << "]\n"
    << "  -ws         size of the context window [" << ws << "]\n"
    << "  -epoch      number of epochs [" << epoch << "]\n"
    << "  -minCount   minimal number of word occurences [" << minCount << "]\n"
    << "  -neg        number of negatives sampled [" << neg << "]\n"
    << "  -wordNgrams max length of word ngram [" << wordNgrams << "]\n"
    << "  -sampling   sampling distribution {sqrt, log, uni} [log]\n"
    << "  -loss       loss function {ns, hs, softmax}   [ns]\n"
    << "  -bucket     number of buckets [" << bucket << "]\n"
    << "  -minn       min length of char ngram [" << minn << "]\n"
    << "  -maxn       max length of char ngram [" << maxn << "]\n"
    << "  -onlyWord   number of words with no ngrams [" << onlyWord << "]\n"
    << "  -thread     number of threads [" << thread << "]\n"
    << "  -verbose    how often to print to stdout [" << verbose << "]\n"
    << "  -t          sampling threshold [" << t << "]\n"
    << "  -label      labels prefix [" << label << "]\n"
    << std::endl;
}

void Args::save(std::ofstream& ofs) {
  if (ofs.is_open()) {
    ofs.write((char*) &(dim), sizeof(int));
    ofs.write((char*) &(ws), sizeof(int));
    ofs.write((char*) &(epoch), sizeof(int));
    ofs.write((char*) &(minCount), sizeof(int));
    ofs.write((char*) &(neg), sizeof(int));
    ofs.write((char*) &(wordNgrams), sizeof(int));
    ofs.write((char*) &(sampling), sizeof(sampling_name));
    ofs.write((char*) &(loss), sizeof(loss_name));
    ofs.write((char*) &(model), sizeof(model_name));
    ofs.write((char*) &(bucket), sizeof(int));
    ofs.write((char*) &(minn), sizeof(int));
    ofs.write((char*) &(maxn), sizeof(int));
    ofs.write((char*) &(onlyWord), sizeof(int));
    ofs.write((char*) &(verbose), sizeof(int));
    ofs.write((char*) &(t), sizeof(double));
  }
}

void Args::load(std::ifstream& ifs) {
  if (ifs.is_open()) {
    ifs.read((char*) &(dim), sizeof(int));
    ifs.read((char*) &(ws), sizeof(int));
    ifs.read((char*) &(epoch), sizeof(int));
    ifs.read((char*) &(minCount), sizeof(int));
    ifs.read((char*) &(neg), sizeof(int));
    ifs.read((char*) &(wordNgrams), sizeof(int));
    ifs.read((char*) &(sampling), sizeof(sampling_name));
    ifs.read((char*) &(loss), sizeof(loss_name));
    ifs.read((char*) &(model), sizeof(model_name));
    ifs.read((char*) &(bucket), sizeof(int));
    ifs.read((char*) &(minn), sizeof(int));
    ifs.read((char*) &(maxn), sizeof(int));
    ifs.read((char*) &(onlyWord), sizeof(int));
    ifs.read((char*) &(verbose), sizeof(int));
    ifs.read((char*) &(t), sizeof(double));
  }
}
