<a id="readme-top"></a>

# Animator
School project to discover the implementation of skeletal animations and understand the mathematical implications of 3D animation.

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#demo">Demo</a>
    </li>
    <li>
    <a href="#built-with">Built With</a>
    </li>
    <li>
      <a href="#testing">Testing</a>
      <ul>
        <li><a href="#steps-details">Steps details</a></li>
        <li><a href="#snippet">Snippet</a></li>
      </ul>
    </li>
    <li>
    <a href="#contact">Contact</a>
    </li>
  </ol>
</details>

<!-- DEMO -->
## Demo

https://github.com/user-attachments/assets/ca26cbee-cbb9-489e-be50-1a2fcbd7341e

<!-- BUILT WITH -->
## Built With

- [![VisualStudio][VS]][VS-url]
- [![C++][C++]][C++-url]

<!-- USAGE DETAILS -->
## Testing

You can see each step I had to follow to work my way to a full anim.
Just uncomment the step you want to look at, and you can also slow time by modifying the slow factor macro at the top of the file.

### <u>Steps details: </u>
1. Draw the skeleton in its BindPose
2. Draw the skeleton for each frame of an animation, one frame at a time
3. Hadrware skinning, bind the model to its skeleton
4. Interpolate between frames
5. Interpolate between 2 aniamtions

### <u>Snippet: </u>
```CPP
void CustomSimulation::Update(float frameTime)
{
	if (frameTime > 0.1f)
	{
		frameTime = FPS_TARGET;
	}
	// frameTime /= SLOW_FACTOR;

	drawWorldMarker();

	// step1(frameTime);
	// step2(frameTime);
	// step3(frameTime);
	// step4(frameTime);
	step5(frameTime);
}
```

<!-- CONTACT -->
## Contact

<u>**Louis "Taur'iil" Dupont**</u>

- [![Linkedin][LinkedIn]][LinkedIn-url]
- [![Git][GitHub]][GitHub-url]
- [![louisdupont.prof@gmail.com][Gmail]][Gmail-url]
- [![ProjectLink]][ProjectLink-url]

<p align="right"><a href="#readme-top">Back to top</a></p>

<!-- MARKDOWN LINKS & IMAGES -->
[VS]: https://img.shields.io/badge/visualstudio-%23a834eb?style=for-the-badge&logo=vs
[VS-url]: https://visualstudio.microsoft.com/fr/
[C++]: https://img.shields.io/badge/C%2B%2B-000000?style=for-the-badge&logo=cplusplus
[C++-url]: https://en.wikipedia.org/wiki/C%2B%2B
[LinkedIn]: https://img.shields.io/badge/linkedin-34a8eb?style=for-the-badge&logo=linkedin
[LinkedIn-url]: linkedin.com/in/louis-dupont-7a80541ba
[GitHub]: https://img.shields.io/badge/github-18191a?style=for-the-badge&logo=github
[GitHub-url]: https://github.com/Tarihle
[Gmail]: https://img.shields.io/badge/copy%40mail-dba9a9?style=for-the-badge&logo=gmail
[Gmail-url]: louisdupont.prof@gmail.com
[ProjectLink]: https://img.shields.io/badge/ProjectLink-a9dbb9?style=for-the-badge&logo=github
[ProjectLink-url]: https://github.com/Tarihle/Animator
