<!-- PROJECT SHIELDS -->
[![cpp-linter](https://github.com/shenxianpeng/cpp-linter-action/actions/workflows/cpp-linter.yml/badge.svg)](https://github.com/HiveBeats/denvlate/blob/main/.github/workflows/cpp-linter.yaml)
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">

<h1 align="center">Denver</h3>

  <p align="center">
    Denver is for Dot-Enver. Simple templating engine to fill scripts and files from .env
    <br />
    <br />
    <a href="https://github.com/HiveBeats/denver/issues">Report Bug</a>
    ·
    <a href="https://github.com/HiveBeats/denver/issues">Request Feature</a>
  </p>
</div>

<!-- ABOUT THE PROJECT -->
## About The Project

It's a templating engine that fills template variables with values from provided .env file. 
<br/>
It was designed to work well for my docker-compose deployments


<!-- GETTING STARTED -->
## Getting Started

### Install
Download the latest binary from the releases page. For example, in order to download version 0.0.5 of this plugin run the following step:\
```sh
curl -LO https://github.com/HiveBeats/denver/releases/download/v0.0.5/denver.linux-amd64.tar.gz
tar xfz denver.linux-amd64.tar.gz
```

Install the binary if you want to:
```sh
cp bin/denver /usr/bin/
```
### Usage
To use this tool you need two things:
 - provide a path for .env file with *-e* argument
 - provide a path for template text file with *-t* argument

Example:
```sh
./denver -e ./test/.env -t ./test/template.txt
```
Result will be visible in that template.txt

### Development

The project is built with **Make**. To build a release version, simply use:
```sh
make
```

Also, Visual Studio Code tasks to build and debug with GCC are attached. 

*build.sh* and *test-prc.sh* scripts here to test the project locally with clang.  



<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/HiveBeats/denver/issues) for a full list of proposed features (and known issues).



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License. See `License` for more information.



<!-- CONTACT -->
## Contact && Donate

Project Link: [https://github.com/HiveBeats/denver](https://github.com/HiveBeats/denver)\
Buy me a coffee:\
BTC 1Nvb7A45ZGmS5zSSyDWWDFV7CnCYGKSUPV\
TON EQBEUaq3T5J8ydqpU_90DCiZ5Gqj-IugXaB_iFW0plUk8cxu



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/HiveBeats/denver.svg
[contributors-url]: https://github.com/HiveBeats/denver/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/HiveBeats/denver.svg
[forks-url]: https://github.com/HiveBeats/denver/network/members
[stars-shield]: https://img.shields.io/github/stars/HiveBeats/denver.svg
[stars-url]: https://github.com/HiveBeats/denver/stargazers
[issues-shield]: https://img.shields.io/github/issues/HiveBeats/denver.svg
[issues-url]: https://github.com/HiveBeats/denver/issues
[license-shield]: https://img.shields.io/github/license/HiveBeats/denver.svg
[license-url]: https://github.com/HiveBeats/denver/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username
[product-screenshot]: images/screenshot.png
