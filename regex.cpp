#include <iostream>
#include <fstream>
#include <regex>
using std::cout;
using std::endl;

//Takes command line input of a file.
int main(int argc, char** argv)
{
  //Defines the regex matching character that finds the link inside of the <a> tag.
  std::regex hyperlink("<a.*href=\"([^\"]+)\".*>.*</a>");

  //Defines the regex match that finds the text that is inside of the <a> tag.
  std::regex linkText("<a.*href=\"[^\"]+\".*>(.*)</a>");

  //Matching elements that store what matched for the text and the link, respectively.
  std::smatch matchText;
  std::smatch matchLink;

  //Defines the regex matching character that finds the link inside of the <img> tag.
  std::regex img("<img.*src=\"([^\"]+)\".*>");

  //Defines the regex match that finds the alt-text inside of the <img> tag.
  std::regex altText("<img.*alt=\"([^\"]+)\".*>");

  //Matching elements that store what matched for the alt-text and the link, respectively.
  std::smatch matchAlt;
  std::smatch matchImg;

  //Stores lines from the file.
  std::string lines;

  //Checks to make sure the number of arguments was correct.
  if (argc != 2)
  {
    cout << "You only need to provide a filename, please try again." << endl;
    return 1;
  }

  //Opens up the file.
  std::ifstream read(argv[1]);

  //Closes the program if the file doesn't open.
  if (!read.is_open())
  {
    cout << "That file cannot be opened. Please provide a valid file." << endl;
    return 1;
  }

  //While loop that reads through the file line by line.
  while (getline(read, lines))
  {
    //Sees if a link is found with the <a> tag, then stores the text.
    if(regex_search(lines, matchText, linkText))
    {
      //Stores the text inside of the link.
      regex_search(lines, matchLink, hyperlink);

      //Outputs the text and the link.
      cout << "Hyperlink Text: " << matchText[1] << endl;
      cout << "Link: " << matchLink[1] << endl << endl;
    }
  }

  //Space between <a> and <img> reading.
  cout << endl;

  //Moves to the beginning of the file.
  read.clear();
  read.seekg(0, std::ios::beg);

  //While loop that reads through the file line by line.
  while (getline(read, lines))
  {
    //Sees if an image is found with the <img> tag, then stores the link.
    if(regex_search(lines, matchImg, img))
    {
      //Stores the alt-text from the image.
      regex_search(lines, matchAlt, altText);

      //Outputs the link
      cout << "Link: " << matchImg[1] << endl;

      //Checks to see if the alt-text is in the image, and prints it out if it is.
      //Prints out not given if there is no alt-text.
      if (!regex_search(lines,matchAlt, altText))
      {
        cout << "Alt-Text: Alt-text not given." << endl << endl;
      }
      else
      {
        cout << "Alt-Text: " << matchAlt[1] << endl << endl;
      }
    }
  }

  return 0;
}
